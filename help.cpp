#include<iostream>
#include<iomanip>
#include<winsock2.h>
using namespace std;



void help(){
  cout<<"Ping\t[ip/域名]\t[-h] [-s] [-n]"<<endl;
  cout<<right<<"\t\t\t-h\t\t显示帮助内容"<<endl<<endl<<endl;
  cout<<right<<"\t\t\t-n count\t要发送回显请求数"<<endl<<endl<<endl;
  cout<<right<<"\t\t\t-s size\t\t发送缓冲区的大小";
}

void checkargs(int argv,char ** args){
    int sizeall = sizeof(*args);
  int sizepart = sizeof(char);
  if(argv<2){
    return;
  }
  else if(argv == 2){
    if(args[1] != "-h"){
      //当参数为个数为2时,按照无选项处理。解析用户ip或域名      
    }
    else{
      //显示帮助信息
      help();
    }
  }
  else{
    //参数个数大于3，此时存在参数
    //解析第二个为主机名或者ip解析不成功则视为参数错误
    //识别第三参数,根据对应参选择，否则识别为未识别的选项

  }
}
void  gethost_v2(sockaddr_in * dst, char * args_1) {
  unsigned long addr = inet_addr(args_1);
  struct hostent *host;
  struct sockaddr_in dst;
  memset(&dst, 0, sizeof(sockaddr_in));
  dst->sin_family = AF_INET;
  dst->sin_port = htons(0);
  if (addr == INADDR_NONE) {
    //不是有效的ip地址,可能是域名
    if (!(host = gethostbyname(args_1))) {
      cout << "请输入正确的主机名或者ip地址" << endl;
      exit(0);
    }
    memcpy(&dst->sin_addr.S_un.S_addr, host->h_addr_list[0], host->h_length);
  } else {
    //输入的是ip地址
    dst->sin_addr.S_un.S_addr = addr;
  }
}

void send_rev(int n,char * sendbuf,const sockaddr_in * dst,sockaddr_in * src,char *revbuf,SOCKET socket){
  for(int i=0;i<n;i++){
  sendto(socket,sendbuf,sizeof(sendbuf),0,(struct sockaddr *) dst,sizeof(dst));
  }
}


int main(int argv,char ** args){
  checkargs(argv,args);
  return 0;
}