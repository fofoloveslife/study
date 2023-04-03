#include<stdio.h>
#include<arpa/inet.h>

int main()
{
    unsigned short host_port = 0x1234;
    unsigned long  host_ip = 0x12345678;
    unsigned short net_port;
    unsigned long  net_ip;

    net_port = htons(host_ip);
    net_ip = htonl(host_ip);

    printf("host_port : %#d \n", host_port);
    printf("net_port : %#d \n", net_port);
    printf("host_ip : %#ld \n", host_ip);
    printf("net_ip : %#ld \n", net_ip);

    return 0;

}