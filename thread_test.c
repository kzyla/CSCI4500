/** ***********************************************************************
	@file	thread_test.c
	@author	Bill Sousan
	@date	March 16, 2020
	@brief	thread example

	C example using pthreads 

	Compiler:	gcc
	Company:	me

*************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>


void * thread_function(void *data);


/** ***********************************************************************
	@brief pthread function

	The function is written to be a pthread using the pthread function
        prototype

	@param[in] data - void * pointer to data needed for this pthread
	@return Returns - void *
*************************************************************************** */
void * thread_function(void *data)
{
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



/** ***********************************************************************
	@brief C main function

	C main function

	@return Returns - int
*************************************************************************** */
int main()
{
	const int MAX_THREADS = 5;	
	int 		i;
	// Table of thread IDs
	pthread_t	threadID_table[MAX_THREADS]; 
	// Table of seconds values passed to each thread
	long		seconds[MAX_THREADS];

	printf("Thread Test\n");

	for(i = 0; i < MAX_THREADS; i++)
	{
		int thread_create_status = 0;	

		seconds[i] = i + 1; // Set number of seconds
		thread_create_status = pthread_create(&threadID_table[i], NULL, 
					thread_function, 
					((void*) &seconds[i]) );

		if(thread_create_status != 0)
		{
			printf("pthread_create error\n");
		}
		
	}

	// sleep(20);

	for(i = 0; i < MAX_THREADS; i++)
	{
                int * thread_retval;
                int   join_retval;
		
		join_retval = pthread_join(threadID_table[i], (void**) (&thread_retval) );
		if(join_retval == 0)
		{
			printf("join> thread retval: %d join retval: %d\n", 
				*thread_retval, join_retval);
		}
		else
		{
			printf("pthread join error: %d\n", join_retval);
		}
	}

	return 0;
}
