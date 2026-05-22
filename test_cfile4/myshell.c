#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <ctype.h>

#define MAXSIZECL 128
#define MAXARGS 32

// shell内部自己维护的第一张表：命令行参数表
// 全局
char* gargv[MAXARGS];
int gargc = 0;
const char* gsep = " ";

// shell自己的工作路径
char cwd[MAXSIZECL];

// 最近一个命令执行完毕的退出码
int lastcode = 0;

// ls -a -l > XX.txt == "ls -a -l" && "XX.txt" && 重定向方式
// 表明重定向的信息
#define NoRedir     0
#define InputRedir  1
#define ApRedir     2
#define OutputRedir 3

char* filename = NULL;		// 保存重定向的目标文件
int redir_type = NoRedir;	// 记录重定向方式



#define TrimSpace(start) do{while(isspace(*start)) ++start;}while(0)



const char* GetUserName() {
	char* un = getenv("USER");
	if (un == NULL) {
		return "None";
	}
	return un;
}


const char* GetPwd() {
	char* pwd = getenv("PWD");
	// char* pwd = getcwd(cwd, sizeof(cwd));
	
	if (pwd == NULL) {
		return "None";
	}
	return pwd;
}

void PrintCommandLine() {
	// 用户名@主机名:当前路径
	printf("%s@%s:%s$ ", GetUserName(), "主机名忽略", GetPwd());
	fflush(stdout);
}

int GetCommand(char commandline[], int size) {
	if (NULL == fgets(commandline, size, stdin)) {
		return 0;
	}
	// 2.1 用户在输入命令时，至少会按一次回车\n
	commandline[strlen(commandline) - 1] = '\0';
	return strlen(commandline);
}



void ParseRedir(char commandline[]) {
	redir_type = NoRedir;
	filename = NULL;
	char* start = commandline;
	char* end = commandline + strlen(commandline);
	while (start < end) {
		if (*start == '>') {
			if (*(start + 1) == '>') {
				// 追加重定向
				*start = '\0';
				++start;
				*start = '\0';
				++start;
				TrimSpace(start);	// 空格
				redir_type = ApRedir;
				filename = start;
				break;
			}
			// 输出重定向
			*start = '\0';
			++start;
			TrimSpace(start);
			redir_type = OutputRedir;
			filename = start;
			break;
		}
		else if (*start == '<') {
			// 输入重定向
			*start = '\0';
			++start;
			TrimSpace(start);
			redir_type = InputRedir;
			filename = start;
			break;
		}
		else {
			++start;	// 没有重定向
		}
	}
}


int ParseCommand(char commandline[]) {
	gargc = 0;
	memset(gargv, 0, sizeof(gargv));
	gargv[0] = strtok(commandline, gsep);
	while (gargv[++gargc] = strtok(NULL, gsep));
	// printf("gargc:%d\n", gargc);

	// int i = 0;
	// for (i; gargv[i]; ++i) {
	// 	printf("gargv[%d]:%s\n", i, gargv[i]);
	// }
	return 0;
}

int ExecuteCommand() {
	pid_t id = fork();
	if (id < 0) {
		return -1;
	}
	else if (id == 0) {
		// 子进程
		int fd = -1;
		if (redir_type == NoRedir) {
			// No
		}
		else if (redir_type == OutputRedir) {
			// 输出重定向
			fd = open(filename, O_WRONLY|O_CREAT|O_TRUNC, 0666);
			dup2(fd, 1);
		}
		else if (redir_type == ApRedir) {
			// 追加重定向
			fd = open(filename, O_WRONLY|O_CREAT|O_APPEND, 0666);
			dup2(fd, 1);
		}
		else if (redir_type == InputRedir) {
			// 输入重定向
			fd = open(filename, O_RDONLY);
			dup2(fd, 0);
		}
		else {
			// bug
		}
		execvp(gargv[0], gargv);
		exit(1);
	}
	else {
		// 父进程
		int wstatus = 0;
		pid_t rid = waitpid(id, &wstatus, 0);
		if (rid > 0) {
			// 等待成功
			lastcode = WEXITSTATUS(wstatus);
			// printf("wait success!\n");
		}
	}
	return 0;
}

// 0：非内建
// 1：内建
int CheckBuildinCommand() {
	if (strcmp(gargv[0], "cd") == 0) {
		// 内建命令
		if (gargc == 2) {
			// 1. 更改内核路径
			chdir(gargv[1]);
			// 2. 更改环境变量
			char buf[100];
			getcwd(buf, sizeof(buf));
			snprintf(cwd, sizeof(cwd), "PWD=%s", buf);
			putenv(cwd);
			lastcode = 0;
		}
		return 1;
	}
	else if (strcmp(gargv[0], "echo") == 0) {
		if (gargc == 2) {
			if (gargv[1][0] == '$') {
				if (strcmp(gargv[1]+1, "?") == 0) {
					printf("lastcode: %d\n", lastcode);
				}
				lastcode = 0;
			}
		}
		return 1;
	}
	return 0;
}

int main() {

	char command_line[MAXSIZECL] = {0};
	while (1) {
		// 1. 打印命令行字符
		PrintCommandLine();

		// 2. 获取字符串输入
		if (0 == GetCommand(command_line, MAXSIZECL)) {
			continue;
		}
		// printf("%s\n",command_line);

		// ls -a -l > XX.txt
		// == "ls -a -l" && "XX.txt" && 重定向方式

		// 3. 
		ParseRedir(command_line);
		// printf("command_line: %s\n", command_line);
		// printf("redir_type: %d\n", redir_type);
		// printf("filename: %s\n", filename);

		// 4. 解析字符串："ls -a -l" -> "ls" "-a" "-l"
		ParseCommand(command_line);
		
		// 5. 这个命令谁来执行？父（内建）还是子？
		if (CheckBuildinCommand()) {	// 1：内建命令
			continue;
		}

		// 6. 让子进程执行命令
		ExecuteCommand();
	}
	return 0;
}
