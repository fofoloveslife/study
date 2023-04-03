linux网络API

~~~c
//服务端
#include<sys/socket.h>
int socket(int domain, int type, int protocol);//创建套接字
//成功返回文件描述符，失败返回-1
//domain套接字中使用的协议族信息 PF_INET IPV4 PF_INET6 IPV6
//type 套接字数据传输类型信息 SOCK_STREAM TCP  SOCK_DGRAM UDP
//protocol 计算机通信中使用的协议信息 大部分情况传递0 除非存在同一协议族中存在多个数据传输方式相同的协议
int tcp_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);//没有数据边界，write和read的次数可以不一样
int udp_socket = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);//有数据边界，wirte和read的次数一样
//TCP套接字和UDP套接字不会共用端口号，所以允许重复


#include(sys/socket.h)
int bind(int sockfd, struct sockaddr *myaddr, socklen_t addrlen);//绑定套接字
//成功返回0，失败返回-1
struct sockaddr_in
{
    sa_fammilu_t   sin_family; //地址族
    uint16_t       sin_port //端口号 网络字节序
    struct in_addr sin_addr//32位IP地址 网络字节序
    char           sin_zero[8];//不使用
}

struct in_addr
{
    In_addr_t s_addr //32位IPV4地址
}

//整型数据大小端转换
//大端存储 网络字节序，小端存储 基本上主机字节序
#include<arpa/inet.h>
unsigned short htons(unsigned short);
unsigned short ntohs(unsigned short);
unsigned long htonl(unsigned long); //常数INADDR_ANY自动huo'qu
unsigned long htonl(unsigned long); 

//点分十进制转网络字节序 即const char* 转换成大端整型
#include<arpa/inet.h>
in_addr_t inet_addr(const char* string);
//返回s_addr，失败返回INADDR_NONE vs2022报错

in_addr_t inet_aton(const char* string, struct in_addr * addr);//利用sockaddr_in结构体中的in_addr结构体
//成功返回1，失败返回0

char* inet_ntoa(struct in_addr addr);//利用sockaddr_in结构体中的in_addr结构体
//成功返回字符串地址，失败返回-1


#include<sys/socket.h>
int listen(int sockfd, int backlog)//监听
//成功返回0，失败返回-1
    
#include<sys/socket.h>
int accept(int sockfd, struck sockaddr *addr, socklen_t *ddrlen);

//客户端
#include<sys/socket.h>
int connect(int sockfd, struct sockaddr* serv_addr,socklen_t addrlen);
//成功返回0，失败返回-1;
~~~

windows网络API

~~~c++
#include<winsock2.h>
int WSAStartup(WORD wVersionRequested, LPWSADATA lpWSAData);//Winsock库初始化
//成功返回0，失败返回错误代码
//WORD 是unsigned short类型 返回版本号高8位为副版本，低8位为主版本号
MAKEWORD(1, 2); //主版本为1，副版本为2，返回0x0201
//LPWSADATA  是WSADATA指针类型,调用函数后相应参数填充已初始化的库信息。

#include<winsock2.h>
int WSACleanup(void) //注销库
//成功返回0失败返回SOCKET_ERROR
    
#include<winsock2.h>
SOCKET socket(int af, int type, int protocol);
//成功返回套接字句柄，失败时返回INVALID_SOCKET

#include<winsock2.h>
int bind(SOCKET s, const struct sockaddr *name, int namelen);
//成功返回0,失败返回SOCKET_ERROR

#include<winsock2.h>
int listen(SOCKET s, int backlog);
//成功返回 0，失败返回SOCKET_ERROR

#include<winsock2.h>
SOCKET accept(SOCKET s, struct sockaddr *addr, int *addrlen);
//成功返回套接字句柄，失败返回INVALID_SOCKET

#include<winsock2.h>
int connect(SOCKET s, const struct sockaddr* name, int namelen)
    
#include<winsock2.h>
int closesocket(SOCKET s)//关闭套接字
//成功返回0 ，失败返回SOCKET_ERR
    
#include<winsock2.h>
int send(SOCKET s， const char * buf, int len, int flags);
//成功返回传输字节数，失败时返回SOCKET_ERROR

#include<winsock2.h>
int recv(SOCKET s, const char* buf, int len, int flags);
//成功返回接受的字节数，失败时返回SOCKET_ERROR 
//flag 接受数据时用到的多种选项信息
~~~

