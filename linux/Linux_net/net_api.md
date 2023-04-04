##tcp

linux 网络API

~~~c
//服务端
#include<sys/socket.h>
int socket(int domain, int type, int protocol);//创建套接字
//成功返回文件描述符，失败返回-1
//domain套接字中使用的协议族信息 PF_INET IPV4 PF_INET6 IPV6
//type 套接字数据传输类型信息 SOCK_STREAM TCP  SOCK_DGRAM UDP
//protocol 计算机通信中使用的协议信息 大部分情况传递0 除非存在同一协议族中存在多个数据传输方式相同的协议
int tcp_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);//没有数据边界，write和read的次数可以不一样,所以客户端要一次循环读取规定大小的字符串
int udp_socket = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);//有数据边界，wirte和read的次数一样
//TCP套接字和UDP套接字不会共用端口号，所以允许重复

#include(sys/socket.h)
int bind(int sockfd, struct sockaddr *myaddr, socklen_t addrlen);//绑定套接字
//成功返回0，失败返回-1
//常数INADDR_ANY绑定的是通配地址，绑定所有的IP

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
uint16_t htons(uint16_t);
uint16_t ntohs(uint16_t);
uint32_t htonl(uint32_t); 
uint32_t htonl(uint32_t); 



//点分十进制转网络字节序 即const char* 转换成大端整型
//只能处理 ipv4 的 ip 地址：
#include<arpa/inet.h>
in_addr_t inet_addr(const char* string);
//返回s_addr，失败返回INADDR_NONE vs2022报错

in_addr_t inet_aton(const char* string, struct in_addr * addr);//利用sockaddr_in结构体中的in_addr结构体
//成功返回1，失败返回0
//windows中不存在

char* inet_ntoa(struct in_addr addr);//利用sockaddr_in结构体中的in_addr结构体
//成功返回字符串地址，失败返回-1

#include<arpa/inet.h>
int inet_pton(int af, const char *src, void *dst); 
//af 地址族AF_INET IPV4 
//src 点分十进制IP地址
//dst 网络字节序的IP地址
//windows 没有

const char *inet_ntop(int af, const void *src, char *dst, socklen_t size);
//af 地址族AF_INET IPV4 
//src 网络字节序的IP地址
//dst 点分十进制IP地址
//size 数组大小
//windows 没有

#include<sys/socket.h>
int listen(int sockfd, int backlog)//监听
//成功返回0，失败返回-1
//sockfd 希望进入等待连接请求状态的套接字文件描述符，成为监听套接字
//backlog 连接请求等待队列的长度，也就是已完成连接队列和未完成连接队列之和的最大值
        
    
#include<sys/socket.h>
int accept(int sockfd, struck sockaddr *addr, socklen_t *ddrlen);
//成功返回创建的套接字文件描述符，失败返回-1
//sockfd 监听套接字
//addr 客户端地址信息
//addlen addr的长度

//客户端
#include<sys/socket.h>
int connect(int sockfd, struct sockaddr* serv_addr,socklen_t addrlen);
//成功返回0，失败返回-1;
//当客户端把请求信息记录到等待队列就完成，不是服务端accept才完成，调用connect后分配客户端的IP和端口
//客户端调用connect函数前，服务端可能先调用accept函数
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

#include<winsock2.h>
INT WSAStringToAddress()//与inet_ntoa和inet_addr一样但是依赖于特点平台降低兼容性
INT WSAAdressToString()//
~~~

## udp

linux

~~~c++
#include<sys/socket.h>
ssize_t sendto(int sock, void *buff,size_t nbytes, int flags, struct sockaddr *to, socklen_t addrlen);
成功返回传输的字节数，失败时返回-1
//sock udp文件描述符
//buff 传输数据的缓冲地址值
//nbytes 待传输的数据长度
//flags 可选参数，若没有则传递0
//to 目标地址信息的sockaddr结构体地址
//addelen sockaddr结构体地址的大小
    
#include<sys/socket.h>
ssize_t recvfrom(int sock, void *buff, size_t nbytes, int flags, struct sockaddr *from, socklen_t *addrlen);
//sock UDP文件描述符
//buff 接受数据的缓冲地址值
//nbytes 可接受的数据的最大长度
//flags 可选参数，若没有则传递0
//from 发送端的sockaddr结构体地址
//addelen sockaddr结构体地址的大小
~~~















































