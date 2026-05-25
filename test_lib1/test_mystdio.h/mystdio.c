#include "mystdio.h"
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>


#define TRY_FLUSH  1
#define MUST_FLUSH 2



// r, w, a, r+, w+, a+
myFILE* myfopen(const char* pathname, const char* mode)	{
	int fd = 0;
	int flags= 0;
	if (strcmp(mode, "r") == 0) {
		flags = O_RDONLY;
		fd = open(pathname, flags);
	}
	else if (strcmp(mode, "w") == 0) {
		flags = O_WRONLY|O_CREAT|O_TRUNC; 
		fd = open(pathname, flags, MODE);
	}
	else if (strcmp(mode, "a") == 0) {
		flags = O_WRONLY|O_CREAT|O_APPEND;
		fd = open(pathname, flags, MODE);
	}
	else {}
	if (fd < 0) {
		return NULL;
	}
	
	myFILE* fp = (myFILE*)malloc(sizeof(myFILE));
	if (fp == NULL) {
		return NULL;
	}

	fp->fd = fd;
	fp->flags = flags;
	fp->flush_mode = LINE_BUFFER;
	fp->cap = SIZE;
	fp->pos = 0;


	return fp;
}





static void myfflushcore(myFILE* fp, int flag) {
	if (fp->pos == 0) {
		return;
	}
	if (fp->flush_mode & LINE_BUFFER || flag & MUST_FLUSH) {
		if ((fp->outbuffer[fp->pos - 1] == '\n') || (flag & MUST_FLUSH)) {
			write(fp->fd, fp->outbuffer, fp->pos);
			fp->pos = 0;
		}
	}
	else if (fp->flush_mode & FULL_BUFFER) {
		// if (fp->pos == fp->cap)
	}
	else if (fp->flush_mode & NO_BUFFER) {
		// write()
	}
	else {}
}


void myflush(myFILE* fp) {
	myfflushcore(fp, MUST_FLUSH);
}

int myfputs(const char* str, myFILE* fp) {
	if (strlen(str) == 0) {
		return 0;
	}
	// 本质向文件缓冲区写
	memcpy(fp->outbuffer + fp->pos, str, strlen(str));
	fp->pos += strlen(str);

	// 条件允许可以自己刷新
	myfflushcore(fp, TRY_FLUSH);

	return strlen(str);
}



void myfclose(myFILE* fp) {
	// 强制刷新
	myflush(fp);

	// 关闭文件
	close(fp->fd);

	// free 
	free(fp);
}
