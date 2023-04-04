#include<stdio.h>
#include<arpa/inet.h>

int main()
{
    unsigned short host_port = 0x1234;
    unsigned int  host_ip = 0x12345678;
    unsigned short net_port;
    unsigned int  net_ip;

    char *addr = "192.163.200.2";
    char *port = "9190"
    struct sockaddr_in sockaddr;


    net_port = htons(host_port);
    net_ip = htonl(host_ip);

    sockaddr.sin_addr.s_addr = inet_addr(addr);
    inet_aton(addr, &sockaddr.sin_addr);
    inet_pton(AF_INET,addr,&sockaddr.sin_addr.s_addr);
    inet_ntop(AF_INET,&sockaddr.sin_addr.s_addr,addr,16);

    
    sockaddr.sin_port = htons(atoi(port));

    printf("host_port : %#x \n", host_port);
    printf("net_port : %#x \n", net_port);
    printf("host_ip : %#lx \n", host_ip);
    printf("net_ip : %#lx \n", net_ip);

    printf("inet_addr s_addr : %#x \n", sockaddr.sin_addr.s_addr);
    printf("inet_aton s_addr : %#x \n", sockaddr.sin_addr.s_addr);
    printf("inet_ntoa char %s \n",inet_ntoa(sockaddr.sin_addr));
    printf("inet_pton : %#x \n", sockaddr.sin_addr.s_addr);
    printf("inet_ntop : %s \n", inet_ntop(AF_INET,&sockaddr.sin_addr.s_addr,addr,16));


    return 0;

}