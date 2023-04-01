#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<errno.h>

int main()
{
    int fd1 = open("./file1.txt", O_RDONLY);//打开存在文件 读文件
    if(fd1 == -1) { 
        perror("open file1");
        exit(1);
    }

    int fd2 = open("./file2.txt",O_WRONLY|O_CREAT,0664); //打开不存在文件 写文件
    if(fd2 == -1) { 
        perror("open file2");
        exit(1);
    }

    char buf[4096];
    int len = -1;
    while (len = read(fd1, buf, sizeof(buf)))
    {
        write(fd2, buf, len);
    }
    close(fd1);
    close(fd2);

    return 0;
    
}