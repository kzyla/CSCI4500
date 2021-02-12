#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <math.h>

int iterations = 0; 
int max_threads = 0;
double logValue = 0;
double value = 0;

pthread_mutex_t lock; 

void * log_function(void *data) {
	long thread = *((long*)data);

	for (int i = 0; i <= iterations; i++) {
		int sign = thread % 2 == 0 ? -1 : 1;
		int N = (i * max_threads) + thread;
		
		pthread_mutex_lock(&lock); 
		value += (sign * pow((logValue - 1), N)) / N;
		pthread_mutex_unlock(&lock); 
	}

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

	max_threads = atoi(argv[2]);	
	iterations = atoi(argv[3]);
	logValue = VALUE;

	pthread_t threadID_table[max_threads]; 
	long threads[max_threads];

	for (int i = 0; i < max_threads; i++) {
		int thread_create_status = 0;	

		threads[i] = i + 1;
		thread_create_status = pthread_create(&threadID_table[i], NULL, log_function, ((void*) &threads[i]));

		if (thread_create_status != 0) {
			printf("pthread_create error\n");
		}
	}
	

	for (int i = 0; i < max_threads; i++) {
		int * thread_retval;
		int   join_retval;
		
		join_retval = pthread_join(threadID_table[i], (void**) (&thread_retval) );

		if (join_retval != 0) {
			printf("pthread join error: %d\n", join_retval);
		}
	}

	pthread_mutex_destroy(&lock); 
	
	printf("%0.14f\n", value);
	printf("%0.14f\n", log(VALUE));
	return 0;
}
