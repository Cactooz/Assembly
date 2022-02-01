/*
 prime.c
 By David Broman.
 Last modified: 2015-09-15
 This file is in the public domain.
*/
#include <stdio.h>

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

int main(void){
	printf("%d\n", is_prime(11));  // 11 is a prime.      Should print 1.
	printf("%d\n", is_prime(383)); // 383 is a prime.     Should print 1.
	printf("%d\n", is_prime(987)); // 987 is not a prime. Should print 0.
}
