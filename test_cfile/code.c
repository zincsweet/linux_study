#include <stdio.h>

int main() {
	const char* filename = "log.txt";
	FILE* fp = fopen(filename, "r");
	if (fp == NULL) {
		perror("fopen");
		return 1;
	}

	// const char* s = "hello world!\n";
	// fputs(s, fp);

	while (1) {
		char buf[128];
		if (NULL == fgets(buf, sizeof(buf), fp)) {
			break;
		}
		printf("from file: %s\n", buf);
	}
	

	fclose(fp);
	fp = NULL;

	return 0;
}
