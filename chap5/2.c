// 2.编写一个打开文件的程序(使用 open 系统调用),然后调用 fork 创建一个新进程。子进程和父进程都可以访问open()返回的文件描述符吗?
// 当它们并发(即同时)写入文件时,会发生什么?
// 答: 子进程和父进程都能访问 fd。存在竞争条件，无法同时使用fd，但最终都会写入成功

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main(){
    int fd = open("./check.txt", O_CREAT | O_RDWR | O_TRUNC, S_IRWXU);
    int pid = fork();
    if (pid < 0) {
        printf("fork error\n");
        exit(1);
    } else if (pid == 0) {
        char *buf = "child\n";
        int error = write(fd, buf, sizeof(char) * strlen(buf));
        printf("child error: %d\n", error == -1 ? 1 : 0);
    } else {
        int wx = wait(NULL);
        char *buf = "parent\n";
        int error = write(fd, buf, sizeof(char) * strlen(buf));
        printf("parent error: %d\n", error == -1 ? 1 : 0);

        int wc = wait(NULL);
        close(fd);
    }
    return 0;
}