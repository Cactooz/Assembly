#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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
	char *numbers = malloc(sizeof(char)*(n-2));

	//Fill the array with 1
	for(int i = 0; i < n-1; i++){
		numbers[i] = 1;
	}

	for(int i = 0; i+2 <= sqrt(n); i++){
		if(numbers[i]){
			//Remove the multiples for the number
			for(int j = (i+2)*(i+2); j <= n; j+=(i+2)){
				numbers[j-2] = 0;
			}
		}
	}

	//Print the numbers
	for(int i = 0; i < n-1; i++)
		if(numbers[i])
			print_numbers(i+2);
	free(numbers);
}

// 'argc' contains the number of program arguments, and
// 'argv' is an array of char pointers, where each
// char pointer points to a null-terminated string.
int main(int argc, char *argv[]){
	if(argc == 2)
		print_sieves(atoi(argv[1]));
	else
		printf("Please state an interger number.\n");
	return 0;
}
