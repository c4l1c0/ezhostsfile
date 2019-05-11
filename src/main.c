#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include"include/curl/getip.h"
#include"include/file/appendhosts.h"
#include"include/file/search.h"
#include"include/file/deleteline.h"

#define LINUX_HOSTS_PATH "/etc/hosts"
#define WINDOWS_HOSTS PATH "C:\\Windows\\System32\\drivers\\etc\\hosts"

void printhelp(){
		printf("Usage: [options] <url>\n\n");

		printf("Options:\n");
		printf("-h\t\t		:Display this message and exit.\n\n");
		printf("-q <key>\t	:Search for entry by supplying key to search.\n");
		printf("-r <key>\t	:Remove entry by searching for key.\n\n");

		printf("For reporting bugs or requesting features, please visit:\n");
		printf("<https://github.com/rezaarifandee/ezhostsfile>\n");
}


int main(int argc, char **argv){
	bool helpflag=0;
	int searchflag=0;
	int deletelineflag=0;

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
				searchflag=i;
			}
			else if(strcmp(argv[i],"-r")==0){
				deletelineflag=i;
			}
			else if(argv[i][0] == '-'){
				helpflag=1;
			}

		}

		if(helpflag) printhelp();
		else if(searchflag>0 || deletelineflag>0){
				if(argv[searchflag+1] == NULL || argv[deletelineflag+1] == NULL){
					printf("ERROR: no search term specified.\n");
				}
				else{
					int *matches=malloc(1);
					if(strcmp(argv[searchflag+1],"-r")==0 || deletelineflag>0){
						int matcheslen=search(LINUX_HOSTS_PATH, argv[deletelineflag+1], &matches);
						if(matcheslen>0){
							int selection;
							printf("Select entry to remove. [1...%d]: ", matcheslen);
							scanf("%d", &selection);
							while(selection>matcheslen || selection<1){
								printf("Invalid input.\n");
								printf("Select entry to remove. [1...%d]: ", matcheslen);
								scanf("%d", &selection);
							}
							selection--;
							if(deleteline(LINUX_HOSTS_PATH, matches[selection])==0) printf("\nSUCCESS: Entry removed.\n");
							else printf("\nERROR: Failed to remove entry.\n");
						}
					}
					else{
						search(LINUX_HOSTS_PATH, argv[searchflag+1], &matches);
					}
				}
				return 0;
		}
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
				if(appendtofile(LINUX_HOSTS_PATH, stringtoappend) == 0) printf("\nSUCCESS: Entry added successfully.\n");
			}
			else{
				printf("\nERROR: Failed to add entry\n");
			}
		}
	}
	return 0;
}
