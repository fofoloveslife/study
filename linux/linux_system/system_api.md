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

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int stat(const char *pathname, struct stat *buf);
int lstat(const char *pathname, struct stat *buf); //lstat (): 得到的是软连接文件本身的属性信息stat (): 得到的是软链接文件关联的文件的属性信息
//pathname文件名
//buf传出参数，传出文件信息
struct stat {
    dev_t          st_dev;        	// 文件的设备编号
    ino_t          st_ino;        	// inode节点
    mode_t         st_mode;      		// 文件的类型和存取的权限, 16位整形数  -> 常用
    nlink_t        st_nlink;     	// 连到该文件的硬连接数目，刚建立的文件值为1
    uid_t          st_uid;       	// 用户ID
    gid_t          st_gid;       	// 组ID
    dev_t          st_rdev;      	// (设备类型)若此文件为设备文件，则为其设备编号
    off_t          st_size;      	// 文件字节数(文件大小)   --> 常用
    blksize_t      st_blksize;   	// 块大小(文件系统的I/O 缓冲区大小)
    blkcnt_t       st_blocks;    	// block的块数
    time_t         st_atime;     	// 最后一次访问时间
    time_t         st_mtime;     	// 最后一次修改时间(文件内容)
    time_t         st_ctime;     	// 最后一次改变时间(指属性)
};

// 类型是存储在结构体的这个成员中: mode_t  st_mode;  
// 这些宏函数中的m 对应的就是结构体成员  st_mode
// 宏函数返回值: 是对应的类型返回-> 1, 不是对应类型返回0
struct stat mystat;

//宏函数判断文件类型
S_ISREG(mystat.st_mode) - 普通文件
S_ISDIR(mystat.st_mode) - 目录
S_ISCHR(mystat.st_mode) - 字符设备
S_ISBLK(mystat.st_mode) - 块设备
S_ISFIFO(mystat.st_mode)- 管道
S_ISLNK(mystat.st_mode) - 软连接
S_ISSOCK(mystat.st_mode)- 本地套接字文件

//与操作判断文件类型
switch(st.st_mode & S_IFMT)
        case S_IFLNK:
            perms[0] = 'l';
            break;
        case S_IFDIR:
            perms[0] = 'd';
            break;
        case S_IFREG:
            perms[0] = '-';
            break;
        case S_IFBLK:
            perms[0] = 'b';
            break;
        case S_IFCHR:
            perms[0] = 'c';
            break;
        case S_IFSOCK:
            perms[0] = 's';
            break;
        case S_IFIFO:
            perms[0] = 'p';
            break;
        default:
            perms[0] = '?';
            break;
    
//判断文件的操作权限
myst.st_mode & S_IRUSR
myst.st_mode & S_IWUSR
myst.st_mode & S_IXUSR
    
#include <unistd.h>
int dup(int oldfd);//复制文件描述符
//成功返回新的文件描述符，失败返回-1

#include <unistd.h>
// 1. 文件描述符的复制, 和dup是一样的
// 2. 能够重定向文件描述符
// 	- 重定向: 改变文件描述符和文件的关联关系, 和新的文件建立关联关系, 和原来的文件断开关联关系
int dup2(int oldfd, int newfd);
//成功返回新的文件描述符，失败返回-1

#include <unistd.h>
#include <fcntl.h>

int fcntl(int fd, int cmd, ... /* arg */ );
//fd文件描述符
//cmd取值
//F_DUPFD	复制一个已经存在的文件描述符与dup一样 成功返回新文件描述符，失败返回-1
//F_GETFL	获取文件的状态标志 成功返回文件的flag，失败返回-1
//F_SETFL	设置文件的状态标志 成功返回文件的flag，失败返回-1
//不是所有的 flag 属性都能被动态修改，只能修改如下状态标志: O_APPEND, O_NONBLOCK, O_SYNC, O_ASYNC, O_RSYNC 等。

#include <sys/types.h>
#include <dirent.h>
// 打开目录
DIR *opendir(const char *name);
//成功返回目录结构体指针，失败返回NULL
//name目录名字



// 读目录
#include <dirent.h>
struct dirent *readdir(DIR *dirp);
//成功返回文件实体指针，失败返回NULL

struct dirent {
    ino_t          d_ino;       /* 文件对应的inode编号, 定位文件存储在磁盘的那个数据块上 */
    off_t          d_off;       /* 文件在当前目录中的偏移量 */
    unsigned short d_reclen;    /* 文件名字的实际长度 */
    unsigned char  d_type;      /* 文件的类型, linux中有7中文件类型 */
    char           d_name[256]; /* 文件的名字 */
};

//关于结构体中的文件类型 d_type，可使用的宏值如下：

//DT_BLK：块设备文件
//DT_CHR：字符设备文件
//DT_DIR：目录文件
//DT_FIFO ：管道文件
//DT_LNK：软连接文件
//DT_REG ：普通文件
//DT_SOCK：本地套接字文件
//DT_UNKNOWN：无法识别的文件类型

// 关闭目录, 参数是 opendir() 的返回值
int closedir(DIR *dirp);
//成功返回0，失败返回-1

// 遍历目录可以opendir 再循环readdir 也可以使用以下函数
#include <dirent.h> 
int scandir(const char *dirp, 
            struct dirent ***namelist,
            int (*filter)(const struct dirent *),
            int (*compar)(const struct dirent **, const struct dirent **));
//成功返回匹配的文件个数，失败返回-1
//dirp: 需要遍历的目录的名字
//namelist: 三级指针，传出参数，需要在指向的地址中存储遍历目录得到的所有文件的信息
//filter: 函数指针，指针指向的函数就是回调函数，需要在自定义函数中指定如果过滤目录中的文件，如果不对目录中的文件进行过滤, 该函数指针指定为NULL即可，如果自己指定过滤函数, 满足条件要返回1, 否则返回 0
//compar: 函数指针，对过滤得到的文件进行排序，可以使用提供的两种排序方式: alphasort: 根据文件名进行排序 versionsort: 根据版本进行排序
int alphasort(const struct dirent **a, const struct dirent **b);
int versionsort(const struct dirent **a, const struct dirent **b);
    struct dirent **namelist = NULL;
    int num = scandir("/fofo", &namelist, istrue, alphasort);
     for(int i=0; i<num; ++i)
    {
        printf("file %d: %s\n", i, namelist[i]->d_name);
        free(namelist[i]); ////记得要释放内存
    }
	free(namelist) //记得要释放内存
~~~

