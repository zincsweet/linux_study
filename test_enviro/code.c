#include<stdio.h>
#include<string.h>
int main(int argc, char *argv[]) {
	if (argc != 2) {
		printf("该命令使用错误！请这样使用：%s -a|-b|-c|-d\n", argv[0]);
		return 1;
	}

	if (strcmp(argv[1], "-a") == 0) {
		printf("执行的是第一种功能\n");
	}
	else if (strcmp(argv[1], "-b") == 0) {
		printf("执行的是第二种功能\n");
	}
	else if (strcmp(argv[1], "-c") == 0) {
		printf("执行的是第三种功能\n");
	}
	else {
		printf("现在执行的是命令默认功能\n");
	}
	// printf("argc: %d\n", argc);
	// int i = 0;
	// for (; i < argc; ++i) {
	//     printf("argc[%d]->%s\n", i, argv[i]);
	// }
	return 0;
}

