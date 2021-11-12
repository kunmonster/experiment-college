#include <string.h>
#include <time.h>
#include <windows.h>
#include <winsock2.h>

#include <iomanip>
#include <iostream>

#pragma comment(lib, "ws2_32.lib")
using namespace std;

#define MAX_BUF_SIZE 1024

// icmp头部
struct icmp {
  unsigned char type;        // type
  unsigned char code;        // code
  unsigned short checksum;   // check_sum
  unsigned short id;         // identcation
  unsigned short sequence;   // sequence
  struct timeval timestamp;  // timestamp
};

// ip头部
struct ip {
  // total 160bit == 20byte
  unsigned char hlen : 4;     // the length of header
  unsigned char version : 4;  // version
  unsigned char tos;          // type of service  8bit
  unsigned short len;         // total length     16bit
  unsigned short id;          // identification   16bit
  unsigned short offset;      // sheetOffset      13bit
  unsigned char ttl;          // time to live     8bit
  unsigned short flag;        // flag of fragment 3bit
  unsigned char protocol;     // protocol         8bit
  unsigned short checksum;    // check_sum of header  16bit
  struct in_addr ipsrc;       // the source ip_address  32bit
  struct in_addr ipdst;       // the destination ip_address  32bit
};

//消息接收缓冲区
char buf_rec[MAX_BUF_SIZE] = {0};

int gettimeofday(struct timeval *, void *);
unsigned short checkSum(unsigned short *, int);
float timediff(struct timeval *, struct timeval *);
void encapsulate(struct icmp *, int);
int unpack(char *, int, char *);
void init_sock();
sockaddr_in gethost(char *);
void help();
void dealargs(int, char **);
void send_rev(int, int, sockaddr_in);

int main(int argc, char *argv[]) {
  system("chcp 65001");
  init_sock();  //初始化winsock
  dealargs(argc, argv);
  system("pause");
  return 0;
}
/**
 * 时间工具
 */
int gettimeofday(struct timeval *tp, void *tzp) {
  time_t clock;
  struct tm tm;
  SYSTEMTIME wtm;
  GetLocalTime(&wtm);
  tm.tm_year = wtm.wYear - 1900;
  tm.tm_mon = wtm.wMonth - 1;
  tm.tm_mday = wtm.wDay;
  tm.tm_hour = wtm.wHour;
  tm.tm_min = wtm.wMinute;
  tm.tm_sec = wtm.wSecond;
  tm.tm_isdst = -1;
  clock = mktime(&tm);
  tp->tv_sec = clock;
  tp->tv_usec = wtm.wMilliseconds * 1000;
  return (0);
}
/**
 * 计算校验和
 * msg 需要校验信息
 * size 需要校验信息的字节数
 *
 */
unsigned short checkSum(unsigned short *msg, int size) {
  // get the check_sum to check the information of the header
  unsigned int check_sum = 0;
  while (size > 1) {
    check_sum += *msg++;
    size -= 2;
  }
  if (size) {
    check_sum += *(unsigned char *)msg;
  }
  check_sum = (check_sum >> 16) + (check_sum & 0xffff);
  check_sum += (check_sum >> 16);
  return (USHORT)(~check_sum);
}

/**
 * 计算时间差
 * begin 开始时间
 * end 结束时间
 */
float timediff(struct timeval *begin, struct timeval *end) {
  int n;
  n = (end->tv_sec - begin->tv_sec) * 100000 + (end->tv_usec - begin->tv_usec);

  //转为毫秒返回
  return (float)(n / 1000);
}

/**
 * 封装ICMP包
 * sourc_icmp 需要封装的ICMP包
 * sequence  该包的序列
 */
void encapsulate(struct icmp *source_icmp, int sequence) {
  source_icmp->type = 8;  // echo reply
  source_icmp->code = 0;
  source_icmp->checksum = 0;   // set the checksum
  source_icmp->id = getpid();  // the id is the process id
  source_icmp->sequence = sequence;
  // memset(&source_icmp->data,0,sizeof(source_icmp->data));
  // for(int i=0;i<256;i++){
  //   source_icmp->data[i] = (char)(65+i%65);
  // }

  gettimeofday(&source_icmp->timestamp, NULL);
  // source_icmp->checksum =
  //     checkSum((unsigned short *)source_icmp, sizeof(icmp)+data_len);
}
/**
 * 对接收到的ip包解包
 *
 */
int unpack(char *buf, int len, char *addr) {
  int i, ipheadlen;
  struct ip *ip;
  struct icmp *icmp;
  float rtt;
  struct timeval end;
  ip = (struct ip *)buf;

  //计算ip首部长度，即ip首部的长度标识乘4
  ipheadlen = ip->hlen << 2;
  //越过ip首部，指向icmp报文
  icmp = (struct icmp *)(buf + ipheadlen);
  // icmp报文总长度
  len -= ipheadlen;
  if (len < 8) {
    printf("ICMP packets\'s length is less than 8 \n");
    return -1;
  }
  if (icmp->type != 0 || icmp->id != getpid()) {
    printf("ICMP packets are not send by us \n");
    return -1;
  }
  gettimeofday(&end, 0);
  rtt = timediff(&icmp->timestamp, &end);
  printf("%d bytes form %s : icmp_seq=%u ttl=%d rtt=%fms \n", len, addr,
         icmp->sequence, ip->ttl, rtt);
  return 0;
}
/**
 * 初始化WINDOWS SOCKET
 */
void init_sock() {
  // init the socket
  WORD wVersionRequested;
  WSADATA wsaData;
  int err;
  wVersionRequested = MAKEWORD(1, 1);
  err = WSAStartup(wVersionRequested, &wsaData);
  if (err != 0) {
    perror("WSAStartup error");
  }
}
/**
 *根据参数获取主机名
 * argc 控制台参数数量
 * argv 控制台参数
 **/
sockaddr_in gethost(char *args_1) {
  unsigned long addr = inet_addr(args_1);
  struct hostent *host;
  struct sockaddr_in dst;
  memset(&dst, 0, sizeof(sockaddr_in));
  dst.sin_family = AF_INET;
  dst.sin_port = htons(0);
  if (addr == INADDR_NONE) {
    //不是有效的ip地址,可能是域名
    if (!(host = gethostbyname(args_1))) {
      std::cout << "请输入正确的主机名或者ip地址" << endl;
      exit(0);
    }
    memcpy(&dst.sin_addr.S_un.S_addr, host->h_addr_list[0], host->h_length);
  } else {
    //输入的是ip地址
    dst.sin_addr.S_un.S_addr = addr;
  }
  return dst;
}

/**
 * 打印帮助信息
 */
void help() {
  cout << "Ping\t[ip/域名]\t[-h] [-s] [-n]" << endl;
  cout << right << "\t\t\t-h\t\t显示帮助内容" << endl << endl << endl;
  cout << right << "\t\t\t-n count\t要发送回显请求数" << endl << endl << endl;
  cout << right << "\t\t\t-s size\t\t发送缓冲区的大小";
}

/**
 * 参数处理
 */
void dealargs(int argc, char **args) {
  int send_num = 4;
  int buf_size = 0;
  if (argc < 2) {
    std::cout << "请输入正确的主机名,ip地址或选项" << endl;
    help();
    exit(0);
  } else if (argc == 2) {
    if (strcmp(args[1], "-h") != 0) {
      //当参数为个数为2时,按照无选项处理。解析用户ip或域名
      sockaddr_in dst = gethost(args[1]);
      send_rev(send_num, 0, dst);
    } else {
      //显示帮助信息
      help();
    }
  } else {
    //参数个数大于3，此时存在参数
    //解析第二个为主机名或者ip解析不成功则视为参数错误
    //识别第三参数,根据对应参选择，否则识别为未识别的选项

    sockaddr_in dst = gethost(args[1]);
    for (int i = 2; i < argc; i++) {
      if (strcmp(args[i], "-n") == 0) {
        send_num = atoi(args[i + 1]);
      } else if (strcmp(args[i], "-s") == 0) {
        buf_size = atoi(args[i + 1]);
      }
    }
    send_rev(send_num, buf_size, dst);
  }
}

/**
 * 发送并接收包
 */
void send_rev(int num, int message_len, sockaddr_in destination) {
  struct sockaddr_in dst = destination;
  struct icmp sourceicmp;
  struct sockaddr_in src;  //存放接收消息的来源的信息

  int n = 0;
  int socket_icmp;
  int src_len = 0;
  int send_res;
  int nsend = 0;
  int received = 0;
  in_addr inaddr;

  memset(&src, 0, sizeof(sockaddr_in));

  if ((socket_icmp = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP)) == -1) {
    // socket创建失败
    std::cout << "socket创建失败" << endl;
    exit(1);
  }

  message_len = message_len > 0 ? message_len : 26;

  for (int i = 0; i < num; i++) {
    memset(&sourceicmp, 0, sizeof(icmp));
    // memset(&icmpPack, 0, sizeof(icmp_pack));
    encapsulate(&sourceicmp, (i + 1));

    char s[sizeof(icmp) + message_len] = {0};
    char tmp[sizeof(icmp)] = {0};
    memcpy(tmp, &sourceicmp, sizeof(icmp));

    for (int j = 0; j < message_len + sizeof(icmp); j++) {
      if (j < 16) {
        s[j] = tmp[j];
      } else {
        s[j] = (char)(65 + (j - 16) % 65);
      }
    }
    sourceicmp.checksum =
        checkSum((unsigned short *)s, sizeof(icmp) + message_len);
    memset(tmp, 0, sizeof(icmp));
    memcpy(tmp, &sourceicmp, sizeof(icmp));
    for (int k = 0; k < 16; k++) {
      s[k] = tmp[k];
    }

    if ((send_res = sendto(socket_icmp, s, sizeof(sourceicmp) + message_len, 0,
                           (struct sockaddr *)&dst, sizeof(dst))) == -1) {
      cout << GetLastError() << endl;
      if (GetLastError() == WSAETIMEDOUT) {
        //超时
        std::cout << "连接已超时" << endl;
      }
      continue;
    }
    src_len = sizeof(src);
    //设置非阻塞模式,设置等待时间:6s
    int TimeOut = 6000;
    memset(&buf_rec, 0, sizeof(buf_rec));
    setsockopt(socket_icmp, SOL_SOCKET, SO_RCVTIMEO, (char *)&TimeOut,
               sizeof(TimeOut));
    memset(&buf_rec, 0, sizeof(buf_rec));
    if ((n = recvfrom(socket_icmp, buf_rec, sizeof(buf_rec), 0,
                      (sockaddr *)&src, &src_len)) < 0) {
      if (GetLastError() == WSAETIMEDOUT) {
        //超时
        std::cout << "连接已超时--目标主机未响应" << endl;
      }
      continue;
    }
    received++;
    if (unpack(buf_rec, n, inet_ntoa(dst.sin_addr)) == -1) {
      printf("unpack() error \n");
    }
    Sleep(1);
  }
}