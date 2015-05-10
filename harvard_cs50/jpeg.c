// Problem Set 5 - JPEG Recovery

#include <stdio.h>
#include <stdlib.h>

#define BLOCK_SIZE 512
#define JPEG_SIGNATURE1 0xe0ffd8ff
#define JPEG_SIGNATURE2 0xe1ffd8ff

int main(int argc, char **argv) {
	argc--; argc++;

	if(argc != 2) {
		printf("usage: recover <card.raw>\n");
		return 1;
	}

	FILE *infile = fopen("./card.raw", "r");
	FILE *outfile = NULL;

	char *buffer = malloc(sizeof(char) * BLOCK_SIZE);
	char filename[12];
	int count = 0;

	// read the raw image 512 bytes at a time (per block)
	while(fread(buffer, sizeof(char), BLOCK_SIZE, infile) == BLOCK_SIZE) {
		// read the first 4 bytes of the block by making a pointer to an integer point to it
		// and determine if it contains a JPEG signature
		int *header = buffer;
		if(*header == JPEG_SIGNATURE1 || *header == JPEG_SIGNATURE2) {
			// close current file and begin writing to a new one
			if(outfile != NULL) {
				fclose(outfile);
			}

			sprintf(filename, "%03d.jpg", ++count);
			outfile = fopen(filename, "w");
			if(outfile == NULL) {
				printf("Could not create file.\n");
				return 1;
			}
			fwrite(buffer, sizeof(char), BLOCK_SIZE, outfile);
		} else {
			// continue writing blocks until we see another JPEG signature
			if(outfile != NULL) {
				fwrite(buffer, sizeof(char), BLOCK_SIZE, outfile);
			}
		}
	}

	free(buffer);
	fclose(infile);
	return 0;
}
