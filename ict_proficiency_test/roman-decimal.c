#include <stdio.h>
#include <ctype.h>
#include <malloc.h>
#include <string.h>

char* decimal_to_roman(int decimal);
int roman_to_decimal(char* roman);

int main(void) {
	int decimal_input;
	char *roman_input = (char*)malloc(sizeof(char) * 120);;
	char *temp;
	char capture_newline;

	while(1) {
		printf("\n\nHindu-Arabic - Roman Converter\n"
			   "---------------------------------\n"
			   "[1] Convert Hindu-Arabic to Roman\n"
			   "[2] Convert Roman to Hindu-Arabic\n"
			   "\n"
			   ">");
		
		switch (getchar()) {
			case '1':
				printf("\n\nEnter Hindu-Arabic number to convert: ");
				scanf("%d%c", &decimal_input, &capture_newline);
				temp = decimal_to_roman(decimal_input);
				printf("\n%d is equal to %s in Roman", decimal_input, temp);
				free(temp);
				break;
			case '2':
				printf("\n\nEnter Roman number to convert: ");
				scanf("%s%c", roman_input, &capture_newline);
				printf("\n%s is equal to %d in Hindu-Arabic", roman_input, roman_to_decimal(roman_input));
				break;
			default:
				continue;
		}

		printf("\n\nConvert another number? (Y/N): ");
		if (toupper(getchar()) == 'Y') 
			continue;
		else
			break;
	}

	return 0;
}

int roman_to_decimal(char* roman) {
	int i, len;
	int decimal = 0;
	for(i = 0, len = strlen(roman); i < len; i++) {
		switch (toupper(roman[i])) {
			case 'M':
				decimal += 1000;
				break;
			case 'D':
				decimal += 500;
				break;
			case 'C':
				if (roman[i + 1] == 'M') {
					decimal += 900;
					i++;
				} else if (roman[i + 1] == 'D') {
					decimal += 400;
					i++;
				} else {
					decimal += 100;
				}
				break;
			case 'L':
				decimal += 50;
				break;
			case 'X':
				if (roman[i + 1] == 'C') {
					decimal += 90;
					i++;
				} else if (roman[i + 1] == 'L') {
					decimal += 40;
					i++;
				} else {
					decimal += 10;
				}
				break;
			case 'V':
				decimal += 5;
				break;
			case 'I':
				if (roman[i + 1] == 'X') {
					decimal += 9;
					i += 2;
				} else if (roman[i + 1] == 'V') {
					decimal += 4;
					i += 2;
				} else {
					decimal += 1;
				}
				break;
		}
	}

	return decimal;
}

char* decimal_to_roman(int decimal) {
	char* roman = (char*)malloc(sizeof(char) * 100);
	int i = 0;

	while(decimal > 0) {
		if (decimal - 1000 >= 0) {
			decimal -= 1000;
			roman[i++] = 'M';
		} else if (decimal - 900 >= 0) {
			decimal -= 900;
			roman[i++] = 'C';
			roman[i++] = 'M';
		} else if (decimal - 500 >= 0) {
			decimal -= 500;
			roman[i++] = 'D';
		} else if (decimal - 400 >= 0) {
			decimal -= 400;
			roman[i++] = 'C';
			roman[i++] = 'D';
		} else if (decimal - 100 >= 0) {
			decimal -= 100;
			roman[i++] = 'C';
		} else if (decimal - 90 >= 0) {
			decimal -= 90;
			roman[i++] = 'X';
			roman[i++] = 'C';
		} else if (decimal - 50 >= 0) {
			decimal -= 50;
			roman[i++] = 'L';
		} else if (decimal - 40 >= 0) {
			decimal -= 40;
			roman[i++] = 'X';
			roman[i++] = 'L';
		} else if (decimal - 10 >= 0) {
			decimal -= 10;
			roman[i++] = 'X';
		} else if (decimal - 9 >= 0) {
			decimal -= 9;
			roman[i++] = 'I';
			roman[i++] = 'X';
		} else if (decimal - 5 >= 0) {
			decimal -= 5;
			roman[i++] = 'V';
		} else if (decimal - 4 >= 0) {
			decimal -= 4;
			roman[i++] = 'I';
			roman[i++] = 'V';
		} else {
			decimal -= 1;
			roman[i++] = 'I';
		}
	}
	roman[i] = '\0';
	return roman;
}