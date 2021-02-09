#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void * thread_function(void *data) {
	long seconds = *((long*)data); // cast pointer to long 
	int i;

	// Loop through number of seconds 		
	for(i = 0; i < seconds; i++)
	{
		sleep(1);
		printf("Thread %lu  count: %d\n", seconds, i);
	}

	printf("Thread %lu exiting...\n", seconds);
	pthread_exit(data); // return pointer to the number of seconds pass to us
}

int main(int argc, char *argv[]) {
	if (argc != 4) {
		printf("Please provide command line arguments <Integer> <Number of Threads> <Num of iterations>\n");
		return 0;
	}

	// const int INTEGER = atoi(argv[1])
	const int MAX_THREADS = atoi(argv[2]);	
	// const int ITERATIONS = atoi(argv[3]);

	// Table of thread IDs
	pthread_t	threadID_table[MAX_THREADS]; 
	// Table of seconds values passed to each thread
	long		seconds[MAX_THREADS];

	for(int i = 0; i < MAX_THREADS; i++) {
		int thread_create_status = 0;	

		seconds[i] = i + 1; // Set number of seconds
		thread_create_status = pthread_create(&threadID_table[i], NULL, 
					thread_function, ((void*) &seconds[i]) );

		if(thread_create_status != 0) {
			printf("pthread_create error\n");
		}
	}

	for(int i = 0; i < MAX_THREADS; i++) {
                int * thread_retval;
                int   join_retval;
		
		join_retval = pthread_join(threadID_table[i], (void**) (&thread_retval) );
		if(join_retval == 0) {
			printf("join> thread retval: %d join retval: %d\n", 
				*thread_retval, join_retval);
		}
		else {
			printf("pthread join error: %d\n", join_retval);
		}
	}

	return 0;
}
