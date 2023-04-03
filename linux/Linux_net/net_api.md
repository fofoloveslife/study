linux网络API

~~~c
//服务端
#include<sys/socket.h>
int socket(int domain, int type, int protocol);//创建套接字
//成功返回文件描述符，失败返回-1

#include(sys/socket.h)
int bind(int sockfd, struct sockaddr *myaddr, socklen_t addrlen);//绑定套接字
//成功返回0，失败返回-1

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
~~~

