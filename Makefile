all:	prog1.c
	gcc -Wall -std=c1x prog1.c -o prog1 -lpthread -lm