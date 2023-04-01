# Linux系统编程

## 文件描述符

虚拟地址空间是一段虚拟的连续的内存地址，起始地址为0，可以用来加载程序数据。

虚拟地址空间的大小也由操作系统决定，32位操作系统的虚拟地址空间大小为2^32字节，也就是4G。

当运行磁盘上一个可执行程序就会得到一个进程，内核会给每一个运行的进程创建一块属于自己的虚拟地址空间，并将应用程序数据装载到虚拟地址空间对应的地址上。

CPU通过MMU从进程的虚拟地址空间映射过去

从操作系统层级来看，虚拟地址空间分为内核区和用户区

<img src="https://subingwen.cn/linux/file-descriptor/image-20210130093015907.png" alt="img" style="zoom:50%;" />

保留区：空指针NULL指向这块地址

.bss： 未初始化及初始化为0的全局变量和静态变量

堆：向高地址扩展，系统用链表维护，地址不连续

栈：向下拓展，内存是连续的、



文件描述符对应于一个打开的文件，文件描述符储存在内核区中的文件描述符表中。

标准 C 库的文件 IO 函数使用的文件指针 FILE* 在 Linux 中也需要通过文件描述符的辅助才能完成读写操作。FILE 其实是一个结构体，其内部有一个成员就是文件描述符

Linux的进程控制块PCB在内核区，本质就是一个task_struct结构体，其中有一个结构体为file即文件描述符表

每一个进程启动后默认分配三个文件描述符0 1 2分别为： STDIN_FILENO：标准输入 、STDOUT_FILENO：标准输出 、STDERR_FILENO：标准错误



##Linux系统文件IO

~~~c++
#include <stdio.h>
#include <errno.h>
void perror(const char *s);//打印错误

#include <fcntl.h>
int open(const char *pathname, int flags, mode_t mode); //打开文件
//成功返回文件描述符，失败返回-1
//pathname 文件名

//flags 指定按什么方式打开文件 
//O_RDONLY: 以只读方式打开文件 
//O_WRONLY: 以只写方式打开文件 
//O_RDWR: 以读写方式打开文件 
//O_APPEND: 新数据追加到文件尾部，不会覆盖文件的原来内容
//O_TRUNC:文件打开会清空
//O_CREAT: 如果文件不存在，创建该文件，如果文件存在什么也不做
//O_EXCL: 检测文件是否存在，必须要和 O_CREAT 一起使用，不能单独
//0_NONBLOCK: 非阻塞打开，只用于打开设备文件，默认为阻塞式

//mode 创建新文件时才需要指定这个参数，用于指定新文件的权限，基本上可以填0664 创建的新文件对应的最终实际权限，计算公式: (mode & ~umask)

#include <unistd.h>
int close(int fd); //关闭文件
//成功返回0，失败返回-1
//fd是文件描述符

#include <unistd.h>
ssize_t read(int fd, void *buf, size_t count);//读文件
//成功返回读取的字节数，失败返回-1
//fd文件描述符
//buf传出参数，存放读取的数据
//count buf指向内存的大小

#include <unistd.h>
ssize_t write(int fd, const void *buf, size_t count);//写文件
//成功返回写入数据的字节数，失败返回-1
//fd文件描述符
//buf存放写入的数据
//count buf指向内存的大小

#include <sys/types.h>
#include <unistd.h>

off_t lseek(int fd, off_t offset, int whence);//文件指针
//成功返回文件指针到头部的偏移量，失败返回-1
//fd文件描述符
//offset 偏移量
//whence 
//SEEK_SET: 从文件头部开始偏移 offset 个字节
//SEEK_CUR: 从当前文件指针的位置向后偏移 offset 个字节
//SEEK_END: 从文件尾部向后偏移 offset 个字节

#include <unistd.h>
#include <sys/types.h>

int truncate(const char *path, off_t length);
int ftruncate(int fd, off_t length); //truncate () 和 ftruncate () 两个函数的区别在于一个使用文件名一个使用文件描述符操作文件，功能相同。
//成功返回0，失败返回-1
//path文件名
//fd文件描述符
//length文件最终大小
~~~

