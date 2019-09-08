#include <ctype.h>
#include <string.h>
#include "utils.h"
#define MAX_BF 1000
#define MAX_CMD 50

int tokenize(char *commands, char * tokens[MAX_CMD]){
	int k=0;
	tokens[k] = strtok(commands," ");
	while(tokens[k] != NULL){
		tokens[++k] = strtok(NULL, " ");
	}
	return k;
}
char* trim(char *s){
	char* end;
	while(isspace(*s))s++;
	end = s+strlen(s)-1;
	while(end > s && isspace(*end))end--;
	*(end + 1) = '\0';
	return s;
}