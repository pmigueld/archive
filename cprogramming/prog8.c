#include <stdio.h>

int main(void) {
	int matrix1[3][3] = {
		{ 5, 2, 1 },
		{ 1, 2, 0 },
		{-2, 0, 4 }
	};
	
	int matrix2[3][3] = {
		{-2,-1,-1 },
		{ 0, 4, 8 },
		{-4, 9, 6 }
	};
	
	int sum[3][3];
	for(int y = 0; y < 3; y++) {
		for(int x = 0; x < 3; x++) {
			sum[y][x] = matrix1[y][x] + matrix2[y][x];
		}
	}
	printf("----------------     ----------------     ----------------\n");
	for(int y = 0; y < 3; y++) {
		printf("| ");
		for(int x = 0; x < 3; x++) {
			printf("%2d | ", matrix1[y][x]);
		}
		printf("%s", (y == 1) ? " +  " : "    ");
		printf("| ");
		for(int x = 0; x < 3; x++) {
			printf("%2d | ", matrix2[y][x]);
		}
		printf("%s", (y == 1) ? " =  " : "    ");
		printf("| ");
		for(int x = 0; x < 3; x++) {
			printf("%2d | ", sum[y][x]);
		}
		printf("\n");
	}
	printf("----------------     ----------------     ----------------\n");
	
	return 0;
}
