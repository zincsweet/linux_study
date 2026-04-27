#include"process.h"

double total = 1024.0;
double speed = 1.0;
double speed_range = 4.3;


double SpeedFloat(double base, double range) {
	int int_range = (int)range;
	return base + rand() % int_range + (range - int_range);
}

void DownLoad(int total) {
	srand(time(NULL));
	double curr = 0.0;
	while (curr <= total) {
		ProcessMax(total, curr);
		curr += SpeedFloat(speed, speed_range);
		if (curr > total) {
			curr = total;
			ProcessMax(total, curr);
			break;
		}
		usleep(30000);
	}
	printf("\n");
}


int main() {
	//Process();
	printf("download:100MB\n");
	DownLoad(100);
	printf("download:300MB\n");
	DownLoad(300);
	printf("download:50MB\n");
	DownLoad(50);
	printf("download:150MB\n");
	DownLoad(150);
	return 0;
}
