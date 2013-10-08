#include <stdio.h>
#include <string.h>
#include <pthread.h>
pthread_t threads[5];
int done[5];
void *thread_main(void *);
int main(void) {
	int i;
	int rc;
	int status;
	printf("pid = %d\n", getpid());
	for(i = 0; i < 5; i++) { 
		done[i] = 0;
		pthread_create(&threads[i], NULL, &thread_main, (void *)i);
		printf("%d, %d\n", i, threads[i]);
	}
	sleep(2);
	for(i=4;i>=0;i--){
		done[i]=1;
	}
	sleep(5);
	return 0;
}
void *thread_main(void *arg) {
	int i;
	double result = 0.0;
	pthread_detach(pthread_self());
	printf("thread: %d, %d\n", (int)arg, getpid());
	while(!done[(int)arg]) {
		for(i = 0; i < 1000000; i++)
			result = result + (double)random(); printf("thread %d, result %e\n", (int)arg, result);
	}
	printf("thread %d terminated.. \n", (int)arg);
	pthread_exit((void*)0);
}
