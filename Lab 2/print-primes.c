/*
 print-prime.c
 By David Broman.
 Last modified: 2015-09-15
 This file is in the public domain.
*/
#include <stdio.h>
#include <stdlib.h>

#define COLUMNS 6

void print_primes(int n){
	// Should print out all prime numbers less than 'n'
	// with the following formatting. Note that
	// the number of columns is stated in the define
	// COLUMNS

	printf("%10d ", 2);
	printf("%10d ", 3);
	printf("%10d ", 5);
	printf("%10d ", 7);
	printf("%10d ", 11);
	printf("%10d ", 13);
	printf("\n");
	printf("%10d ", 17);
	printf("%10d ", 19);

	printf("\n");
}

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

int is_prime(int n){
	//Return instantly if n = 0 or 1
	if(n == 0 || n == 1) return 0;
	
	//If n can be divided return 0
	for(int i = 2; i < n/2; i++) {
		if(n%i == 0) return 0;
	}

	//Else return 1
	return 1;
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
