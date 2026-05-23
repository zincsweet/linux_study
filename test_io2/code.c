#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>


int main() {
	printf("hello world");
	sleep(2);
	_exit(0);
	return 0;
}
