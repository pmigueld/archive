#include <stdio.h>

typedef unsigned short bool;

bool multiple_of_3(int n) { return n % 3 == 0; }
bool multiple_of_5(int n) { return n % 5 == 0; }

int main(void) {
	for(int i = 1; i <= 100; i++) {
		if(!multiple_of_3(i) && !multiple_of_5(i)) {
			printf("%d", i);
		}

		if (multiple_of_3(i)) printf("Fizz");
		if (multiple_of_5(i)) printf("Buzz");

		printf("\n");
	}

	return 0;
}