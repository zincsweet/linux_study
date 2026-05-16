#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>

int main() {
	printf("我是父进程：%d\n", getpid());
	sleep(3);
	pid_t id = fork();
	if (id == 0) {
		// child
		while (1) {
			printf("我是子进程：%d， 我父亲的进程：%d\n", getpid(), getppid());
			sleep(1);
		}
	}
	else {
		// father
		while (1) {
			printf("我是父进程：%d\n", getpid());
			sleep(1);
		}
	}

	return 0;
}
