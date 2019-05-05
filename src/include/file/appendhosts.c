#ifndef APPENDTOFILE_H
#include"appendhosts.h"

int appendtofile(char *path, char* content){
	FILE *file;

	file = fopen(path, "a+");
	fprintf(file, content);
	fprintf(file, "\n");
	fclose(file);
}
#endif
