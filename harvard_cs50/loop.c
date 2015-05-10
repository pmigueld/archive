#include <stdio.h>
#include <stdlib.h>

void f(int x) {
	void (*F[2])(int) = {f, exit};
	printf("%d\n", x);
	F[x / 1000](x + 1);
}

int main(void) {
	f(1);
	return 0;
}

