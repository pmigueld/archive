/************************************************
 | Reverse Number Addition
 | ICT Proficiency Examination - C Programming
 |
 | @author Paolo Miguel N. de Leon
 | @date   November 24, 2012
 ************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUFFER 1024

typedef char* string;

int parse_int(string s) {
    int i;
    sscanf(s, "%d", &i);
    return i;
}

string to_string(int i) {
    string s = (string) malloc(sizeof(char) * MAX_BUFFER);
    sprintf(s, "%d", i);
    return s;
}

void reverse(string input) {
    char temp;

    int i = 0, j = strlen(input) - 1;
    while(i <= j) {
        temp = input[i];
        input[i] = input[j - i];
        input[j - i] = temp;
        i += 1;
    }
}

int compute_line(string line) {
    string token, temp;
    int sum = 0;

    token = strtok(line, ' ');
    sum += parse_int(reverse(token));
    while((token = strtok(NULL, ' '))) {
        sum += parse_int(reverse(token));
    }

    temp = reverse(to_string(sum));
    sum = parse_int(temp);
    free(temp);
    return sum;
}

int main(void) {
    // FILE* input = fopen("c_in.txt", "r");
    // FILE* output = fopen("c_out.txt", "w");

    string buffer = (string) malloc(sizeof(char) * MAX_BUFFER);

    while(fgets(buffer, MAX_BUFFER, stdin)) {
        buffer[strlen(buffer) - 1] = '\0';

        printf("%d\n", compute_line(buffer));
        // fprintf(output, "%d\n", compute_line(buffer));
    }

    free(buffer);
    return 0;
}
