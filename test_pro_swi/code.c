#include<stdio.h>
#include<unistd.h>

int main() {
	printf("我变成了一个进程：%d\n", getpid());
	// 执行另一个程序
	execl("/usr/bin/ls","-a","-l",NULL);	// 程序替换函数


	printf("我的代码运行中...");
	printf("我的代码运行中...");
	printf("我的代码运行中...");
	printf("我的代码运行中...");
	return 0;
}
