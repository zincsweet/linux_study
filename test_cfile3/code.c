#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>


int main() {
	umask(0);
	close(1);          // 关闭标准输出
	int fd = open("a.txt",O_WRONLY|O_CREAT,0664);
	printf("测试文字");// 不会打印屏幕，全部写入a.txt
	return 0;
}
