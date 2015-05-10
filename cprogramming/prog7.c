#include <stdio.h>

int main(void) {
    int i, sum = 0, input;
    char c;
    printf("Enter 10 numbers.\n");
    for(i = 1; i <= 10; i++) {
        printf("Enter %d%s number: ", i, (i == 1) ? "st" :
                                         (i == 2) ? "nd" :
                                         (i == 3) ? "rd" : "th");
        scanf("%d%c", &input, &c);
        sum += input;
    }
    printf("The sum of the ten numbers is %.2f\n", sum / (float)i);

    return 0;
}
