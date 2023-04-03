#include<stdio.h>
#include<stdlib.h>
#include<WinSock2.h>
#pragma warning(disable:4996)
void error_handling(char* message);

int main(int argc, char*argv[])
{
    WSADATA wsaData;
    SOCKET sock;
    SOCKADDR_IN server_addr;

    char message[30];
    int str_len;

    if(argc != 3) {
        printf("Usage : %s <IP> <port>\n", argv[0]);
        exit(1);
    }

    if(WSAStartup(MAKEWORD(2,2),&wsaData) != 0) 
        error_handling("WSAStarup() error");


    sock = socket(PF_INET, SOCK_STREAM, 0);
    if(sock == INVALID_SOCKET) error_handling("socket() error");

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family=AF_INET;
    server_addr.sin_addr.s_addr=inet_addr(argv[1]);
    server_addr.sin_port=htons(atoi(argv[2]));

    if(connect(sock,(SOCKADDR*) &server_addr,sizeof(server_addr)) == SOCKET_ERROR) 
        error_handling("connect() error");

    str_len = recv(sock, message, sizeof(message) - 1, 0);
    if(str_len == -1) error_handling("read() error");
    printf("Message from server: %s \n", message);
    
    closesocket(sock);
    WSACleanup();
    return 0;

}
void error_handling(char *message) {
    fputs(message, stderr);
    fputc('\n',stderr);
    exit(1);
}
