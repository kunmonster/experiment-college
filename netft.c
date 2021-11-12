/* Simple demo showing how to communicate with Net F/T using C language. */

/*#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#pragma comment(lib, "wsock32.lib")
//#include <arpa/inet.h>
#include <sys/types.h>
//#include <sys/socket.h>
#include <winsock.h>
//#include <netdb.h>
//#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib")
*/

#include "winsock2.h"
#pragma  comment(lib,"ws2_32.lib")

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
//#include <iostream>


#define PORT 49152 /* Port the Net F/T always uses 通常使用端口*/
#define COMMAND 2 /* Command code 2 starts streaming 命令代码2开始流*/

/* Typedefs used so integer sizes are more explicit 使用Typedefs使整数大小明确*/
typedef unsigned int uint32;
typedef int int32;
typedef unsigned short uint16;
typedef short int16;
typedef unsigned char byte;
typedef struct response_struct {
uint32 rdt_sequence;
uint32 ft_sequence;
uint32 status;
int32 FTData[6];
} RESPONSE;

int main(int* a, int* b, int* c, int* d, int* e, int* f) {

WORD wVersionRequest;
WSADATA wsaData;
wVersionRequest = MAKEWORD(2, 2);
int err1 = WSAStartup(wVersionRequest, &wsaData);

SOCKET socketHandle; /* Handle to UDP socket used to communicate with Net F/T. 处理用于Net F/T通讯的UDP套接字*/
struct sockaddr_in addr; /* Address of Net F/T. Net F/T的ip地址*/
struct hostent* he; /* Host entry for Net F/T. Net F/T的主机条目*/
char request[8];//byte request[8]; /* The request data sent to the Net F/T. 发送到Net F/T的请求数据*/
RESPONSE resp; /* The structured response received from the Net F/T. 从Net F/T接受到的结构体*/
char response[36];//byte response[36]; /* The raw response data received from the Net F/T. 从Net F/T接受到的原始数据*/
int i; /* Generic loop/array index. 通用 环/数组 索引*/
int err; /* Error status of operations. 操作错误状态*/
const char* AXES[] = { "Fx", "Fy", "Fz", "Tx", "Ty", "Tz" }; /* The names of the force and torque axes. */

/* Calculate number of samples, command code, and open socket here. 计算样本数 命令代码  打开socket*/
socketHandle = socket(AF_INET, SOCK_DGRAM, 0);
//socketHandle = socket(2, 2, 0);
if (socketHandle == -1) {
exit(1);
}

*(uint16*)&request[0] = htons(0x1234); /* standard header. 标准头*/
*(uint16*)&request[2] = htons(COMMAND); /* per table 9.1 in Net F/T user manual. 根据用户手册表9.1*/
*(uint32*)&request[4] = htonl(1); /* see section 9.1 in Net F/T user manual. 用户手册9.1节*/


/* Sending the request. 发送请求*/

he = gethostbyname("192.168.1.1");
//he = getaddrinfo("192.168.1.1");
//hostent* phost = gethostbyname("");

/*

he->h_addrtype= gethostbyname("192.168.1.1")->h_addrtype;
he->h_addr_list = gethostbyname("192.168.1.1")->h_addr_list;
he->h_aliases = gethostbyname("192.168.1.1")->h_aliases;
he->h_length = gethostbyname("192.168.1.1")->h_length;
he->h_name = gethostbyname("192.168.1.1")->h_name;
*/


memcpy(&addr.sin_addr, he->h_addr_list[0], he->h_length);
addr.sin_family = AF_INET;
addr.sin_port = htons(PORT);

err = connect(socketHandle, (struct sockaddr*)&addr, sizeof(addr));
if (err == -1) {
exit(2);
}
send(socketHandle, request, 8, 0);

/* Receiving the response. 接受响应*/
recv(socketHandle, response, 36, 0);
resp.rdt_sequence = ntohl(*(uint32*)&response[0]);
resp.ft_sequence = ntohl(*(uint32*)&response[4]);
resp.status = ntohl(*(uint32*)&response[8]);
for (i = 0; i < 6; i++) {
resp.FTData[i] = ntohl(*(int32*)&response[12 + i * 4]);
}

/* Output the response data. 输出响应数据*/
int guo[6];
//printf("Status: 0x%08x\n", resp.status);
for (i = 0; i < 6; i++) {
printf("%s: %d\t\n", AXES[i], resp.FTData[i]);
// guo[i] = resp.FTData[i];
}
// *a = guo[0];
// *b = guo[1];
// *c = guo[2];
// *d = guo[3];
// *e = guo[4];
// *f = guo[5];
return 0;


// char str[50]={'\0'};
// char stm[50]={'\0'};
// for(int s = 0;s<6;s++)
// {
// sprintf(str,"%d",guo[s]);
// strcat(stm,str);
// strcat(stm,"+");
// }
// printf("%s",stm);
// int a = atoi(stm);
// printf("%d",a);

// return a;



//return "hello123132132131321321321321";
}