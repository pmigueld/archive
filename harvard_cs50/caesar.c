// Problem Set 2 - Caesar's Cipher
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
char *caesar(char *p, int k);
void usage(void);
 
int main(int argc, char **argv) {
    argc--; argv++;

    int k;
    char p[100];
    
    if(argc == 1 && atoi(argv[0])) {
        k = (int)atoi(argv[0]);
        printf("Plain Text:  ");
        sscanf(p, "%[^\n]", fgets(p, 100, stdin));
    } else {
        usage();
    }
    
    printf("Cipher Text: %s", caesar(p, k));
    
    return 0;
}

void usage(void) {
    printf("caesar <k>\n");
    printf("k - non-negative integer key\n");
    exit(0);
}

char *caesar(char *p, int k) {
    char *c = (char *)malloc(sizeof(char) * strlen(p));
    
    int i;
    for(i = 0; i < strlen(p); i++) {
        if(isupper(p[i])) {
            c[i] = (p[i] - 'A' + k) % 26 + 'A';
        } else if(islower(p[i])) {
            c[i] = (p[i] - 'a' + k) % 26 + 'a';
        } else if(isspace(p[i])) {
            c[i] = ' ';
        } else if(!isalnum(p[i])) {
            c[i] = p[i];
        }
    }
    
    return c;
}
