#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>

#define BUF_SIZE 30
void error_handling(char* message);

int main(int argc, char*argv[])
{
    int server_sock;
    char message[BUF_SIZE];
    int str_len;
    socklen_t client_addr_size;
    struct sockaddr_in server_addr, client_addr;

    if(argc != 2)
    {
        printf("Usage : %s <port>\n", argv[0]);
        exit(1);
    }
    
    server_sock = socket(PF_INET, SOCK_DGRAM, 0);
    if(server_sock == -1) 
        error_handling("socket() error");

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family=AF_INET;
    server_addr.sin_addr.s_addr=htonl(INADDR_ANY);
    server_addr.sin_port=htons(atoi(argv[1]));

    if(bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) 
        error_handling("bind() error");

    while(1)
    {
        client_addr_size = sizeof(client_addr);
        str_len = recvfrom(server_sock, message, BUF_SIZE, 0, 
            (struct sockaddr*)&client_addr, &client_addr_size);
        sendto(server_sock, message, str_len, 0,
            (struct sockaddr*)&client_addr, client_addr_size);
    }
    close(server_sock);
    return 0;

}

void error_handling(char *message) {
    fputs(message, stderr);
    fputc('\n',stderr);
    exit(1);
}
