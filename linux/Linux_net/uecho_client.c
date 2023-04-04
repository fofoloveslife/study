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
    int sock;
    char message[BUF_SIZE];
    int str_len;
    socklen_t from_addr_size;
    struct sockaddr_in server_addr, from_addr;

    if(argc != 3)
    {
        printf("Usage : %s <IP> <port>\n", argv[0]);
        exit(1);
    }
    
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if(sock == -1) 
        error_handling("socket() error");

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family=AF_INET;
    server_addr.sin_addr.s_addr=inet_addr(argv[1]);
    server_addr.sin_port=htons(atoi(argv[2]));

    while(1)
    {
        fputs("Insert message(q to qujit)", stdout);
        fgets(message, sizeof(message), stdin);
        if(!strcmp(message,"q\n") || !strcmp(message,"Q\n") )
            break;

        sendto(sock, message, strlen(message), 0,
            (struct sockaddr*)&server_addr, sizeof(server_addr));

        from_addr_size = sizeof(from_addr);
        str_len = recvfrom(sock, message, BUF_SIZE, 0,
            (struct sockaddr*)&from_addr, &from_addr_size);
        message[str_len] = 0;
        printf("Message from server : %s", message);
 
    }
    close(sock);
    return 0;

}

void error_handling(char *message) {
    fputs(message, stderr);
    fputc('\n',stderr);
    exit(1);
}
