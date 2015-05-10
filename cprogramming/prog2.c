#include <stdio.h>

int main(void) {
	int i, input;
	char c;
	for(i = 8; i <= 23; i++) {
		printf("Enter the number %d: ", i);
		scanf("%d%c", &input, &c);
		if(input != i) {
			printf("Try again!\n");
			i--;
		}
	}
	printf("Mission Accomplished!\n");
	
	return 0;
}
