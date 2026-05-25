#include "mystdio.h" 
#include "mystring.h"
#include <unistd.h>


int main() {
	myFILE* fp = myfopen("log.txt", "w");
	if (fp == NULL) {
		printf("myfopen error!\n");
		return 0;
	}

	// int cnt = 10;
	//const char* str = "hello myio";
	//while (cnt--) {
	//	myfputs(str, fp);
	//	sleep(1);
	//	printf("debug: outbuffer: %s, pos: %d\n", fp->outbuffer, fp->pos);
	//}

	myfclose(fp);
	printf("wtite file success!\n");
	mystrlen();
	return 0;
}
