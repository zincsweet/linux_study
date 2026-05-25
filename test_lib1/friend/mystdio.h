#pragma once
#include <stdio.h>

#define SIZE 1024

#define NO_BUFFER   1	// 000..001
#define LINE_BUFFER 2	// 000..010
#define FULL_BUFFER 4	// 000..100


#define MODE 0666

typedef struct _myFILE {
	int fd;
	int flags;
	int flush_mode;
	char outbuffer[SIZE];
	int pos;
	int cap;

}myFILE;



myFILE* myfopen(const char* pathname, const char* mode);	// r, w, a, r+, w+, a+
int myfputs(const char* str, myFILE* fp);
void myfflush(myFILE* fp);
void myfclose(myFILE* fp);
