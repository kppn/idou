#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>


long long diff_time(struct timespec ts_before, struct timespec ts_after)
{
	return (ts_after.tv_sec * 1000000000 + ts_after.tv_nsec) -
		(ts_before.tv_sec * 1000000000 + ts_before.tv_nsec);
}


char msg_buf[256];


#define TRY 10000

int main()
{
	FILE * fp = fopen("hoge", "w");
	unsigned long long diff_times[TRY];
	int i;

	char msg[256];
	for (i = 0; i < 255; i++) 
		msg[i] = 'a';
	msg[255] = '\0';

	struct timespec ts_before;
	struct timespec ts_after;
	for (i = 0; i < TRY; i++) {
		clock_gettime(CLOCK_REALTIME, &ts_before);

		//fputs(msg, fp);
		//memcpy(msg_buf, msg, 256); memcpy(msg_buf, msg, 256);

		//fflush(fp);

		clock_gettime(CLOCK_REALTIME, &ts_after);

		diff_times[i] = diff_time(ts_before, ts_after);
	}

	fclose(fp);

	for (i = 0; i < TRY; i++)
		printf("%07d %lld\n", i, diff_times[i]);
}

