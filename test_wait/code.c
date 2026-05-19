#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<error.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>

int main() {
	pid_t id = fork();
	if(id == 0) {
		int cnt = 5;
		while (1) {
			printf("我是子进程, pid: %d\n", getpid());
			sleep(1);
		}
		exit(0);
	}
	else if (id > 0) {
		// while (1) {
		// 	  printf("我是父进程, pid : %d\n", getpid());
		//    sleep(1);
		// }

		// sleep(10);	// 便于观察到子进程的僵尸状态
		
		// 等待子进程
		// pid_t rid = wait(NULL);
		int wstatus = 0;
		pid_t rid = waitpid(id, &wstatus, 0);
		if (rid == id) {
			// 等待成功
			int exit_code = ((wstatus >> 8)&0xff); // 1111 1111
			int exit_sig = wstatus&0x7f; // 0111 1111
			printf("pid: %d, wait success!, wstatus: %d, exit_code: %d, exit_sig: %d\n", getpid(), wstatus, exit_code, exit_sig);
		}
		// sleep(5);
	}

	return 0;
}
