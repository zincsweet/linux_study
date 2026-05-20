#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int main() {
	printf("我变成了一个进程：%d\n", getpid());
	// 执行另一个程序
	char *const envp[] = {"PATH=/bin:/usr/bin", "TERM=console", NULL};	
	execle("/bin/ps", "ps", "-ef",NULL, envp);	// 程序替换函数
	exit(1);

	return 0;
}
