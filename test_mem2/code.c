#include<stdio.h>
#include<unistd.h>

int g_val = 100;

int main() {
	printf("g_val: %d, &g_val: %p\n", g_val, &g_val);

	pid_t id = fork();
	if (id == 0) {
		while (1) {
			printf("我是子进程，pid: %d, ppid: %d, g_val: %d, &g_val: %p\n", getpid(), getppid(), g_val, &g_val);
			sleep(1);
			++g_val;
		}
	}
	else {
		while (1) {
			printf("我是父进程，pid: %d, ppid: %d, g_val: %d, &g_val: %p\n", getpid(), getppid(), g_val, &g_val);
			sleep(1);
		}
	}
	return 0;
}
