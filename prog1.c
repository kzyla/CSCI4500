#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <math.h>

double logValue = 0;

void * log_function(void *data) {
	pthread_exit(data);
}

int main(int argc, char *argv[]) {
	if (argc != 4) {
		printf("Please provide command line arguments <Integer> <Number of Threads> <Num of iterations>\n");
		return 0;
	}

	const double VALUE = atof(argv[1]);
	if (VALUE <= 0 || VALUE > 2) {
		printf("Please provide an integer between the interval 0 < x <= 2\n");
		return 0;
	}

	const int MAX_THREADS = atoi(argv[2]);	
	// const int ITERATIONS = atoi(argv[3]);

	logValue = VALUE;

	pthread_t threadID_table[MAX_THREADS]; 

	for (int j = 0; j < MAX_THREADS; j++) {
		int thread_create_status = 0;	

		thread_create_status = pthread_create(&threadID_table[j], NULL, log_function, NULL);

		if (thread_create_status != 0) {
			printf("pthread_create error\n");
		}
	}

	for (int i = 0; i < MAX_THREADS; i++) {
		int * thread_retval;
		int   join_retval;
		
		join_retval = pthread_join(threadID_table[i], (void**) (&thread_retval) );

		if (join_retval != 0) {
			printf("pthread join error: %d\n", join_retval);
		}
	}
	
	printf("%0.14f\n", logValue);
	printf("%0.14f\n", log(VALUE));
	return 0;
}
