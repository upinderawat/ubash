#include <ctype.h>
#include <string.h>
#include "utils.h"

char *trim(char *s){
	char* end;
	while(isspace(*s))s++;
	end = s+strlen(s)-1;
	while(end > s && isspace(*end))end--;
	*(end + 1) = '\0';
	return s;
}