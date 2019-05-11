#include<stdio.h>
#include<string.h>
#include"include/curl/getip.h"
#include"include/file/appendhosts.h"
#include"include/file/search.h"
#include"include/file/deleteline.h"

#define LINUX_HOSTS_PATH "/etc/hosts"
#define WINDOWS_HOSTS PATH "C:\\Windows\\System32\\drivers\\etc\\hosts"

void printhelp(){
		printf("Usage: [options] <url>\n\n");

		printf("Options:\n");
		printf("-h\t	:Display this message and exit.\n\n");
		printf("-q <key>\t	:Search for entry by supplying key to search.\n\n");

		printf("For reporting bugs or requesting features, please visit:\n");
		printf("<https://github.com/rezaarifandee/ezhostsfile>\n");
}


int main(int argc, char **argv){
	int helpflag=0;
	int searchflag=0;

	if(argc==1){
		printhelp();
	}
	else{
		for(int i = 1; i < argc; i++){
			if(strcmp(argv[i],"-h")==0){
				helpflag=1;
				break;
			}
			else if(strcmp(argv[i],"-q")==0){
				search(LINUX_HOSTS_PATH, argv[i+1]);
				return 0;
			}
		}

		if(helpflag) printhelp();
		else{
			printf("url:\t%s\n", argv[1]);
			char *ip = getip(argv[1]); //get ip from api
			if(ip!=NULL){
				printf("ip:\t%s\n", ip);
				char *stringtoappend=malloc(strlen(ip) + 2 + strlen(argv[1]));
				stringtoappend[0] = '\0';
				strcat(stringtoappend, ip);
				strcat(stringtoappend, " ");
				strcat(stringtoappend, argv[1]);
				if(appendtofile(LINUX_HOSTS_PATH, stringtoappend) == 0) printf("\nSUCCESS: Entry added successfully\n");
			}
			else{
				printf("\nERROR: Failed to add entry\n");
			}
		}
	}
	return 0;
}
