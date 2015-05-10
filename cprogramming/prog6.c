#include <stdio.h>

void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

void bubbleSort(int *array) {
    for(int y = 0; y < 5; y++) {
        for(int x = 0; x < 4; x++) {
            if(array[x + 1] > array[x]) {
                swap(&array[x + 1], &array[x]);
            }
        }
    }
}

int main(void) {
    int array[5];
    char c;
    for(int i = 0; i < 5; i++) {
        printf("Enter a number: ");
        scanf("%d%c", &array[i], &c);
    }

    bubbleSort(array);

    for(int i = 0; i < 5; i++) {
        printf("%d\n", array[i]);
    }

    return 0;
}
