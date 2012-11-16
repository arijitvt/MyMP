#include<stdio.h>
#include<string.h>
#include<time.h>
#include<unistd.h>
#include<ipc/libipc.h>

int main(){
	char *data = "Arijit Chattopadhyay has build the ipc library";
	int count = strlen(data);
	struct 	timespec starttime;
	struct timespec endtime;
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&starttime);
	Hyb_ASend(0,data,count);
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&endtime);
	printf("Time taken in nano secs %lu\n",(endtime.tv_nsec-starttime.tv_nsec));
	return 0;

}
