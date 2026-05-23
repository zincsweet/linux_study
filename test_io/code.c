#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>


int main() {
	close(1);
	int fd = open("log.txt", O_WRONLY|O_CREAT|O_TRUNC, 0666);
	printf("fd is : %d\n",fd);	// stdout -> 1
	fflush(stdout);
	close(fd);
	return 0;
}
