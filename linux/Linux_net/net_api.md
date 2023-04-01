网络API

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

