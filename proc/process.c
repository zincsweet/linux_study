#include"process.h"

#define SIZE 101
#define STYLE '='


void ProcessMax(double total, double curr) {
	if (curr > total) {
		curr = total;
	}
	double rate = curr / total * 100;
	int num = (int)rate;
	char bar[SIZE];
	memset(bar, '\0', sizeof(bar));
	int i;
	for (i = 0; i < num; ++i) {
		bar[i] = STYLE;
	}

	static const char* lable = "|/-\\";
	static int index = 0;

	printf("[%-100s] [%.1f%%] [%c]\r", bar, rate, lable[index++]);
	index %= strlen(lable);
	fflush(stdout);
}


void Process() {
	const char* lable = "|/-\\";
	int len = strlen(lable);
	char bar[SIZE];
	memset(bar, '\0', sizeof(bar));
	int proc = 0;
	while (proc <= 100) {
		printf("[%-100s] [%d%%] [%c]\r", bar, proc, lable[proc%len]);
		fflush(stdout);
		bar[proc++] = STYLE;
		usleep(30000);
	}
	printf("\n");
}
