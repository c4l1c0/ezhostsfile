#ifndef SEARCH_H
#include"search.h"

int search(char *path, char *key, int **matches){
	FILE *file;
	int flag = 0;
	int line = 1;
	int found = 0;
	char tmp[512];
	int *new_matches=(int*) malloc(1*sizeof(int));

	file = fopen(path, "a+");

	if(file==NULL){
			if(errno == EACCES) printf( "Error opening file: %s\n", strerror( errno ) );
			return -1;
	}

	while(fgets(tmp, 512, file) != NULL){
		if(strstr(tmp, key) != NULL){
			if(tmp[0]=='#') continue;
			printf("[%d] Found at line: %d\n", found+1, line);
			printf("\t%s\n", tmp);
			new_matches[found]=line;
			found++;
			new_matches = (int*) realloc(new_matches, (found+1)*sizeof(int));
		}
		line++;
	}

	*matches=(int*) realloc(new_matches, (found*sizeof(int)));

	if(found==0) printf("No matches\n");

	fclose(file);

	return found;
}
#endif
