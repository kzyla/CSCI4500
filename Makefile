all:	thread_test.c
	gcc -Wall -std=c1x thread_test.c -o prog1 -lpthread -lm