#include <stdio.h>

int main(void) {
	int i = 8, input;
	char c;
	while(i <= 23) {
		printf("Enter the number %d: ", i);
		scanf("%d%c", &input, &c);
		if(input != i) {
			printf("Try again!\n");
		} else {
			i++;
		}
	}
	printf("Mission Accomplished!\n");
	
	return 0;
}
