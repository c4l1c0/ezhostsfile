#ifndef SEARCH_H
#include"search.h"

int search(char *path, char *key){
	FILE *file;
	int flag = 0;
	int line = 1;
	int found = 0;
	char tmp[512];

	file = fopen(path, "a+");

	if(file==NULL){
			if(errno == EACCES) printf( "Error opening file: %s\n", strerror( errno ) );
			return -1;
	}

	while(fgets(tmp, 512, file) != NULL){
		if(strstr(tmp, key) != NULL){
			if(tmp[0]=='#') continue;
			printf("[%d] Found at line: %d\n", found, line);
			printf("\t%s\n", tmp);
			found++;
		}
		line++;
	}

	if(found==0) printf("No matches\n");

	fclose(file);

	return found;
}
#endif
