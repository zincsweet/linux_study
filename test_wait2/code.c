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
		while (cnt--) {
			printf("我是子进程, pid: %d\n", getpid());
			sleep(1);
		}
		exit(10);
	}
	else {
		// while (1) {
		// 	  printf("我是父进程, pid : %d\n", getpid());
		//    sleep(1);
		// }

		// sleep(10);	// 便于观察到子进程的僵尸状态
		
		// 等待子进程
		// pid_t rid = wait(NULL);
		while (1) {
			int wstatus = 0;
			pid_t rid = waitpid(id, &wstatus, WNOHANG);
			if (rid > 0) {
				printf("wait success,退出的子进程是: %d, exit_code: %d\n",rid, WEXITSTATUS(wstatus));
				break;
			}
			else if (rid == 0) {
				printf("子进程还在运行，父进程还得等！\n");
				sleep(2);
			}
			else {
				perror("waitpid\n");
				break;
			}
		}
		// sleep(5);
	}

	return 0;
}
