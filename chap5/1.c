#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void test1();

void test2();

int main(int argc, char *argv[]) {
    if (argc == 1) {
        test1();
    } else {
        test2();
    }
    return 0;
}

void test1() {
    int pid = fork();
    int x = 100;
    if (pid < 0) {
        printf("fork error\n");
        exit(1);
    } else if (pid == 0) {
        printf("child, x %d\n", x);
    } else {
        printf("parent, x %d\n", x);
    }
}

void test2() {
    int pid = fork();
    int x = 100;
    if (pid < 0) {
        printf("fork error\n");
        exit(1);
    } else if (pid == 0) {
        printf("child,x %d\n", x);
        x = 0;
        printf("child,x %d\n", x);
    } else {
        printf("parent,x %d\n", x);
        x = 1;
        printf("parent,x %d\n", x);
    }
}

// 1.编写一个调用 fork()的程序。在调用之前,让主进程访问一个变量(例如 x)并将其值设置为某个值(例如 100)。子进程中的变量有什么值?当子进程和父进程都改变 x 的值时,变量会发生什么?

// 答: 子进程父进程各自一份 x 变量,修改互不影响