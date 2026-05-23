#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>


int main() {
	// 向显示器打印字符串
	// C语言
	printf("hello printf\n");
	fprintf(stdout, "hello fprintf\n");
	const char* s = "hello fputs\n";
	fputs(s, stdout);

	// 系统调用
	const char* s2 = "hello write\n";
	write(1, s2, strlen(s2));

	fork();
	return 0;
}
