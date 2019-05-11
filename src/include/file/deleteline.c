#ifndef DELLINE_H
#include"deleteline.h"

int deleteline(char *path, int line){
	char *tmppath;
	FILE *file;
	FILE *tmpfile;
	char tmp[512];
	int linepointer=1;

	if((tmppath = malloc(255)) != NULL){
		tmppath[0] = '\0';
		strcat(tmppath, path);
		strcat(tmppath, "tmp");
	}

	file = fopen(path, "r");
	tmpfile = fopen(tmppath, "w+");

	if(file==NULL){
		if(errno == EACCES) printf("Error opening file: %s\n", strerror(errno));
		return -1;
	}
	if(tmpfile==NULL){
		if(errno == EACCES) printf("Error creating temporary file: %s\n", strerror(errno));
		return -1;
	}


	while(fgets(tmp, 512, file) != NULL){
		if(linepointer != line){
			fputs(tmp, tmpfile);
		}
		linepointer++;
	}

	fclose(file);
	fclose(tmpfile);

	remove(path);
	rename(tmppath, path);

	return 0;
}
#endif
