#include <stdio.h>
#include <stdlib.h>

#define COLUMNS 6

int currentColumn = 0;
void print_numbers(int n){
	//Print the number
	printf("%10d", n);
	
	//Add a column to the counter
	currentColumn++;

	//Print a new line after the correct amount of COLUMNS
	if(currentColumn%COLUMNS == 0)
		printf("\n");
}

void print_sieves(int n){
	int numbers[n-2];

	//Fill the array with the numbers from 2
	for(int i = 2; i < n; i++){
		numbers[i] = i;
	}
}
void print_primes(int n){
	// Should print out all prime numbers less than 'n'
	// with the following formatting. Note that
	// the number of columns is stated in the define
	// COLUMNS
	for(int i = 2; i <= n; i++){
		print_sieves(i);
	}
}

// 'argc' contains the number of program arguments, and
// 'argv' is an array of char pointers, where each
// char pointer points to a null-terminated string.
int main(int argc, char *argv[]){
	if(argc == 2)
		print_primes(atoi(argv[1]));
	else
		printf("Please state an interger number.\n");
	return 0;
}
