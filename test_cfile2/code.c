#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>


int main() {
	umask(0);
	int fd = open("log.txt", O_WRONLY|O_CREAT|O_APPEND, 0666);
	int fda = open("loga.txt", O_WRONLY|O_CREAT|O_APPEND, 0666);
	int fdb = open("logb.txt", O_WRONLY|O_CREAT|O_APPEND, 0666);
	if (fd < 0) {
		perror("open");
	}
	printf("fd: %d\n", fd);
	printf("fda: %d\n", fda);
	printf("fdb: %d\n", fdb);

	const char* buf = "ABC\n";
	write(fd, buf, strlen(buf));

	close(fd);
	return 0;
}
