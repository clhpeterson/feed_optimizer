#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define TRUE 1
#define FALSE 0

int random_int (int max);


int main (int argc, char** argv)
{
	int N = 10000;
	int H = 2000;
	int W = 2000;
	int time = 1;
	printf ("%d %d %d\n", N, W, H);
	for (int i = 0; i < N; i++){
		int random = random_int (10);
		if (random > 7){
			printf ("R %d\n", time);
		} else {
			printf ("S %d %d %d\n", time, random_int (1000000), random_int (10));
		}
		time += 1;
	}
}

int random_int (int max)
{
	return rand()%max+1;
}

