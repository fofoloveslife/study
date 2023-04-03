#include<stdio.h>
#include<arpa/inet.h>

int main()
{
    unsigned short host_port = 0x1234;
    unsigned long  host_ip = 0x12345678;
    unsigned short net_port;
    unsigned long  net_ip;

    char *addr = "192.163.200.2";
    struct sockaddr_in sockaddr;


    net_port = htons(host_ip);
    net_ip = htonl(host_ip);

    sockaddr.sin_addr.s_addr = inet_addr(addr);
    inet_aton(addr, &sockaddr.sin_addr)

    printf("host_port : %#x \n", host_port);
    printf("net_port : %#x \n", net_port);
    printf("host_ip : %#lx \n", host_ip);
    printf("net_ip : %#lx \n", net_ip);

    printf("inet_addr s_addr : %#lx \n", s_addr);
    printf("inet_aton s_addr : %#lx \n", sockaddr.sin_addr.s_addr);
    printf("inet_ntoa char %s ",inet_ntoa(sockaddr.sin_addr));

    return 0;

}