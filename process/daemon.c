#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

/*
创建守护进程模型
1.	创建子进程，父进程退出
所有工作在子进程中进行形式上脱离了控制终端
2.	在子进程中创建新会话
　　	setsid()函数
　　	使子进程完全独立出来，脱离控制
3.	改变当前目录为根目录
　　	chdir()函数
　　	防止占用可卸载的文件系统
　　	也可以换成其它路径
4.	重设文件权限掩码
　　	umask()函数
　　	防止继承的文件创建屏蔽字拒绝某些权限
　　	增加守护进程灵活性
5.	关闭文件描述符
　　	继承的打开文件不会用到，浪费系统资源，无法卸载
6.	开始执行守护进程核心工作
7.	守护进程退出处理程序模型	
*/

void daemonize(void)
{
    pid_t pid;
    /*
     * * 成为一个新会话的首进程，失去控制终端
     * */
    if ((pid = fork()) < 0) {
        perror("fork");
        exit(1);
    } else if (pid != 0) /* parent */
        exit(0);
    setsid();
    /*
     * * 改变当前工作目录到/目录下.
     * */
    if (chdir("/") < 0) {
        perror("chdir");
        exit(1);
    }
    /* 设置umask为0 */
    umask(0);
    /*
     * * 重定向0，1，2文件描述符到 /dev/null，因为已经失去控制终端，再操作0，1，2没有意义.
     * */
    close(0);
    open("/dev/null", O_RDWR);
    dup2(0, 1);
    dup2(0, 2);
}

int main(void)
{
    daemonize();
    while(1); /* 在此循环中可以实现守护进程的核心工作 */
}
