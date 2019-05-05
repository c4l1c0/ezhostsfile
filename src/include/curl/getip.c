#include"getip.h"

static size_t handleResponse(void *contents, size_t size, size_t nmemb, void *userp){
	size_t resp_size = size*nmemb;
	struct string *response = (struct string *) userp;

	char *ptr = realloc(response->str, response->len + resp_size +1);
	if(ptr == NULL) {
		fprintf(stderr, "Failed to allocate memory for response.\n");
		return 0;
	}
	
	response->str = ptr;
	memcpy(&(response->str[response->len]), contents, resp_size);
	response->len += resp_size;
	response->str[response->len] = 0;
	return resp_size;
}


char * getip(char *url){
	CURL *curl;
	CURLcode res;

	char *url_for_api;
	char *ip;
	
	struct string chunk;
	chunk.len = 0;
	chunk.str = malloc(1);

	if((url_for_api = malloc( strlen("http://ip-api.com/line/") + strlen(url) + 1)) != NULL ){
		url_for_api[0] = '\0';
		strcat(url_for_api, "http://ip-api.com/line/");
		strcat(url_for_api, url);
	}

	curl = curl_easy_init();
	if(curl){
		curl_easy_setopt(curl, CURLOPT_URL, url_for_api);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, handleResponse);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);

		res = curl_easy_perform(curl);

		if(res != CURLE_OK) {
			fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
			curl_easy_cleanup(curl);
			free(chunk.str);
			curl_global_cleanup();
			return NULL;
		}
		else {
			int i;
			bool lastline = 0;
			for(i=chunk.len-1; i>=0;i--){
				if(chunk.str[i]=='\n' && lastline==1) break;
				else lastline=1;
			}
			i++;
			ip = malloc(chunk.len-i-1);
			for(int j = i; j<chunk.len-1; j++){
				ip[j-i] = chunk.str[j];
			}
		}
	}
	else {
		fprintf(stderr, "curl_easy_init() failed: %s\n", curl_easy_strerror(res));
		curl_easy_cleanup(curl);
		free(chunk.str);
		curl_global_cleanup();
		return NULL;
	}
	curl_easy_cleanup(curl);
	free(chunk.str);
	free(url_for_api);
	curl_global_cleanup();
	return ip;
}
