/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * Bare minimum empty user application template
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# "Insert system clock initialization code here" comment
 * -# Minimal main function that starts with a call to board_init()
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */
#include <asf.h>
#include <stdio.h>
#include <stdlib.h>

#define SEED 123

int x[10];
void initArray(int a[], int size, int min, int max, int seed);
void printArray(int a[], int size, char name[]);
void sortArray(int a[], int size);
int main()
{
	initArray(x, 10, 10, 100, SEED);
	printArray(x, 10, "array x");
	sortArray(x, 10);
	printArray(x, 10, "array x Sorted");
	return 0;
}
void initArray(int a[], int size, int min, int max, int seed) {
	for(int i = 0; i < size; i++) {
		x[i] = rand() % (max - min) + min; //  (100-10) [0,90] then add 10 using min so range is [10,100]
	}
}
void sortArray(int a[], int size){
	for(int j =0; j < (size -1); j++) {
		for (int l = 0; j < (size - j -1); l++) {
			if (x[l] > x[l+1]) {
			    int swap = x[l];
			    x[l] = x[l+1];
			    x[l+1] = swap;
			}
		}
	}

}
void printArray(int a[], int size, char name[]){
	printf("%s/n", name);
	for (int i = 0; i < size; i++) {
	printf("%d\n", x[i]);
	}
}