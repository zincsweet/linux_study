#include <stdio.h>
#include <stdlib.h>


int main() {
	printf("hello\n");         // 走 stdout(1)  正常消息
	perror("open failed");     // 走 stderr(2)  错误信息
	fprintf(stderr, "error");  // 走 stderr(2)
	return 0;
}
