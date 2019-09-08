#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include "execute_cmd.h"
void execute_cmd(char *file, char *argv[]){
	if(execvp(file, argv)==-1){
		perror("Could'nt execute command");
		exit(1);
	}
}