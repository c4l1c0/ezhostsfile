#ifndef APPENDTOFILE_H
#include"appendhosts.h"

int appendtofile(char *path, char* content){
	FILE *file;
	int flag = 0;

	file = fopen(path, "a+");

	if(file==NULL){
			if(errno == EACCES) printf( "Error opening file: %s\n", strerror( errno ) );
			return -1;
	}

	if(fprintf(file, content)==strlen(content)) flag++;
	if(fprintf(file, "\n")==1) flag++;

	fclose(file);

	if(flag==2) return 0;
	else {
		return -1;
	}
}
#endif
