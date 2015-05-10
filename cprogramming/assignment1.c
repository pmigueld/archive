#include <stdio.h>
#include <stdlib.h>

int count(char *s) {
	int i = 0; 

	while(s[++i] != '\0');

	return i;
}

char *concat(char *s1, char *s2) {
	int length = count(s1) + count(s2);
	char *string = (char *)malloc(sizeof(char) * length);
	int len1 = count(s1), i = 0;
	int len2 = count(s2), j = 0;
	
	while(string[i++] = s1[i],   i < len1);
	while(string[i++] = s2[j++], j < len2);

	string[i] = '\0';
	return string;
}

int main(void) {
	char str[128], s1[128], s2[128], c;

	printf("Enter a string: ");
	scanf("%[^\n]%c", str, &c);
	printf("=> Your string contains %d characters.\n", count(str));
	printf("Enter another string: ");
	scanf("%[^\n]%c", s1, &c);
	printf("Enter a string to append to the previous string: ");
	scanf("%[^\n]%c", s2, &c);
	char *temp = concat(s1, s2);
	printf("=> %s\n", temp);

	free(temp);
	return 0;
}
