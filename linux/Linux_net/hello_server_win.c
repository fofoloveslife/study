#include<stdio.h>
#include<stdlib.h>
#include<WinSock2.h>

void error_handling(const char* message);

int main(int argc, char* argv[])
{
    WSADATA wsaData;

    SOCKET server_sock;
    SOCKET client_sock;

    SOCKADDR_IN server_addr;
    SOCKADDR_IN client_addr;

    int client_addr_size;
    char message[] = "Hello World";

    if (argc != 2)
    {
        printf("Usage : %s <port>\n", argv[0]);
        exit(1);
    }

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
        error_handling("WSAStarup() error");


    server_sock = socket(PF_INET, SOCK_STREAM, 0);//创建服务端套接字
    if (server_sock == INVALID_SOCKET)
        error_handling("socket() error");

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(atoi(argv[1]));

    if (bind(server_sock, (SOCKADDR*)&server_addr, sizeof(server_addr)) == SOCKET_ERROR)
        error_handling("bind() error");
    if (listen(server_sock, 5) == SOCKET_ERROR)
        error_handling("listen() error");

    client_addr_size = sizeof(client_addr);
    client_sock = accept(server_sock, (struct sockaddr*)&client_sock, &client_addr_size);
    if (client_sock == SOCKET_ERROR)
        error_handling("accept() error");

    send(client_sock, message, sizeof(message), 0);
    closesocket(server_sock);
    closesocket(client_sock);
    WSACleanup();
    return 0;

}

void error_handling(const char* message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
