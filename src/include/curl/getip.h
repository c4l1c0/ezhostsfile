#ifndef GETIP_H
#define GETIP_H
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<curl/curl.h>

#define apiurl "http://ip-api.com/line/"

struct string {
	char *str;
	size_t len;
};

static size_t handleResponse(void *contents, size_t size, size_t nmemb, void *userp);


char * getip(char *url);
#endif
