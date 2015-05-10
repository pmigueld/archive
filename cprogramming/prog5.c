#include <stdio.h>

int main(void) {
	int i, min = 1 << 30, input;
	char c;
	printf("Enter 10 numbers.\n");
	for(i = 1; i <= 10; i++) {
		printf("Enter %d%s number: ", i, (i == 1) ? "st" : 
										 (i == 2) ? "nd" : 
										 (i == 3) ? "rd" : "th");
		scanf("%d%c", &input, &c);
		min = (input < min) ? input : min;
	}
	printf("The smallest number is %d\n", min);
	return 0;
}
