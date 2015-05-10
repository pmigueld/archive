// Problem Set 2 - Vigenere's Cipher
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
char *vigenere(char *p, char *k);
void usage(void);
 
int main(int argc, char **argv) {
	argc--; argv++;

	char *k;
	char p[100];
	
	if(argc == 1) {
		int i;
		for(i = 0; i < strlen(argv[0]); i++) {
			if(!isalpha(argv[0][i])) {
				usage();
			}
		}
		
		k = argv[0];
		printf("Plain Text:  ");
		sscanf(p, "%[^\n]", fgets(p, 100, stdin));
	} else {
		usage();
	}
	
	printf("Cipher Text: %s", vigenere(p, k));
	
	return 0;
}
 
void usage(void) {
	printf("vigenere <k>\n");
	printf("k - alphabetic keyword\n");
	exit(0);
}

char *vigenere(char *p, char *k) {
	char *c = (char *)malloc(sizeof(char) * strlen(p));
	
	int i, j;
	for(i = 0; i < strlen(p); i++) {
		if(j < strlen(k)) {
			if(!isalnum(p[i])) {
				c[i] = p[i];
			} else if(isupper(p[i])) {
				c[i] = (p[i] - 'A' + (k[j] - 'A')) % 26 + 'A';
				j++;
			} else if(islower(p[i])) {
				c[i] = (p[i] - 'a' + (k[j] - 'a')) % 26 + 'a';
				j++;
			}
		} else {
			j = 0;
			i--;
		}
	}
	
	return c;
}
