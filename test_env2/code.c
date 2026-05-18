#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
// int main(int argc, char* argv[], char* env[]) {
// 	(void)argc;	// 防止不用此参数报警
// 	(void)argv;
// 	int i = 0;
// 	for (; env[i]; ++i) {
// 		printf("env[%d]: %s\n", i, env[i]);
// 	}
// 	printf("我是一个命令，自己实现的！\n");
// 	return 0;
// }

int main() {
	// extern char** environ;
	// int i = 0;
	// for (; environ[i]; ++i) {
	//     printf("environ[%d]->%s\n", i, environ[i]);
	// }
	char* whoami = getenv("USER");
	printf("用户：%s\n", whoami);
	if (whoami == NULL) {
		printf("无法执行我，不认识用户\n");
	}
	else if (strcmp(whoami, "root") == 0) {
		printf("root也不能执行！\n");
	}
	else if (strcmp(whoami, "zincsweet") == 0) {
		printf("你是合法用户，可执行!\n");
	}
	else {}
	return 0;
}
