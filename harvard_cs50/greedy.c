#include <stdio.h>

int main(void) {
    int php1000 = 0,
        php500  = 0,
        php200  = 0,
        php100  = 0,
        php50   = 0,
        php20   = 0,
        php10   = 0,
        php5    = 0,
        php1    = 0,
        cent25  = 0;

    float cost, payment, change;

    do {
        printf("You're items cost 1233.50\n"
               "Enter payment: ");
        scanf("%f", &payment);
        cost = 1233.50;
        change = payment - cost;
    } while (change < 0);
    printf("Change = %.2f\n", change);
    while(1) {
        if(change - 1000 > 0) {
            php1000++;
            change -= 1000;
        } else if(change - 500 > 0) {
            php500++;
            change -= 500;
        } else if(change - 200 > 0) {
            php200++;
            change -= 200;
        } else if(change - 100 > 0) {
            php100++;
            change -= 100;
        } else if(change - 50 > 0) {
            php50++;
            change -= 50;
        } else if(change - 20 > 0) {
            php20++;
            change -= 20;
        } else if(change - 10 > 0) {
            php10++;
            change -= 10;
        } else if(change - 5 > 0) {
            php5++;
            change -= 5;
        } else if(change - 1 > 0) {
            php1++;
            change -= 1;
        } else if(change - 0.25 >= 0) {
            cent25++;
            change -= 0.25;
        }
        if(change == 0) { break; }
    }

    printf("1000 pesos: %d\n"
           " 500 pesos: %d\n"
           " 200 pesos: %d\n"
           " 100 pesos: %d\n"
           "  50 pesos: %d\n"
           "  20 pesos: %d\n"
           "  10 pesos: %d\n"
           "   5 pesos: %d\n"
           "   1 peso:  %d\n"
           "  25 cents: %d\n",
           php1000, php500, php200, php100, php50,
           php20, php10, php5, php1, cent25);

    return 0;
}
