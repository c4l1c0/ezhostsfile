#include<stdio.h>
#include<string.h>
#include"include/curl/getip.h"
#include"include/file/appendhosts.h"
#include"include/file/search.h"
#include"include/file/deleteline.h"

void printhelp(){
		printf("Usage: [options] <url>\n\n");

		printf("Options:\n");
		printf("-h\t	:Display this message and exit.\n\n");

		printf("For reporting bugs or requesting features, please visit:\n");
		printf("<https://github.com/rezaarifandee/ezhostsfile>\n");
}


int main(int argc, char **argv){
	int helpflag=0;

	if(argc==1){
		printhelp();
	}
	else{
		for(int i = 1; i < argc; i++){
			if(strcmp(argv[i],"-h")==0){
				helpflag=1;
				break;
			}
		}

		if(helpflag) printhelp();
		else{
			printf("%s\n", argv[1]);
			char *ip = getip(argv[1]); //get ip from api
			char *stringtoappend=malloc(strlen(ip) + 2 + strlen(argv[1]));
			stringtoappend[0] = '\0';
			strcat(stringtoappend, ip);
			strcat(stringtoappend, " ");
			strcat(stringtoappend, argv[1]);
			if(appendtofile("/etc/hosts", stringtoappend) == 0) printf("Entry added successfully\n");
		}
	}
	return 0;
}
