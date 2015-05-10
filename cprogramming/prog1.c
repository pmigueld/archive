#include <stdio.h>

int main(void) {
	int input; char c;
	printf("Enter a number: ");	scanf("%d%c", &input, &c);
	printf("%s\n", (input >= 56 && input <= 78) ? "YOU WIN" : "YOU LOSE");
	
	return 0;
}
