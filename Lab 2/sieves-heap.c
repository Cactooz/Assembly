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
	//Just print 2, if n = 2
	if(n == 2) {
		printf("2");
		return;
	}
	
	int *numbers = malloc(sizeof(int)*(n-2));

	//Fill the array with the numbers from 2
	for(int i = 2; i < n; i++){
		numbers[i-2] = i;
	}

	for(int i = 0; i < n-2; i++){
		if(numbers[i] != 0){
			//Print the number
			print_numbers(numbers[i]);

			//Remove the multiples for the number
			for(int j = i; j < n-2; j += numbers[i]){
				if(j != i)
					numbers[j] = 0;
			}
		}
	}
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
