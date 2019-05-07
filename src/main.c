#include<stdio.h>
#include<string.h>
#include"include/curl/getip.h"
#include"include/file/appendhosts.h"

int main(int argc, char **argv){
	printf("%s\n", argv[1]);
	char *ip = getip(argv[1]); //get ip from api
	char *stringtoappend=malloc(strlen(ip) + 2 + strlen(argv[1]));
	stringtoappend[0] = '\0';
	strcat(stringtoappend, ip);
	strcat(stringtoappend, " ");
	strcat(stringtoappend, argv[1]);
	if(appendtofile("/etc/hosts", stringtoappend) == 0) printf("Entry added successfully\n");
	return 0;
}
