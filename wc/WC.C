#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <ctype.h>

#define MAXLINE 4096

#define TRUE 1
#define FALSE 0

int main(int argc, char *argv[])
{
	typedef int BOOL;
	FILE *fp;
	char line[MAXLINE];
	unsigned long lc = 0, wc = 0, cc = 0;
	size_t len;
	int i;
	BOOL in_word = FALSE;

	if (argc != 2) {
		printf("Please supply the name of a single Wordstar file in this directory\n");
		return 1;
	}

	if ((fp = fopen(argv[1], "rb")) == NULL) {
		perror(fp) ;
		return 1;
	}

	while ((fgets(line, MAXLINE, fp)) != NULL) {
		len = strlen(line);
		for (i = 0; i < len; i++){
			if (isspace(line[i])){
				in_word = TRUE;
			} else if (in_word) {
				in_word = FALSE;
				wc++;
			}
		}
		lc++;
		cc += len;
	}

	if (ferror(fp) != 0) {
		perror(fp);
	}

	printf("%ld, %ld, %ld\n", lc, wc, cc);
	fclose(fp);

	return 0;
}