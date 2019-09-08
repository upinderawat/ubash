#include <bits/stdc++.h>
#include <unistd.h>//for read(), STDIN_FILENO
#include <string.h>
#include "execute_cmd.h"
#define MAX_BF 1000
#define MAX_CMD 50
using namespace std;

int main(int argc, char const *argv[]){
	//load config files
	const char ps1 []= "$: ";
	char* input_buffer;
	char* commands[MAX_CMD];

	int ncmds;

	
	while(true){
		ncmds = 0;
		input_buffer = (char *)malloc(MAX_BF);
		if(write(STDOUT_FILENO, ps1, sizeof(ps1)-1)==-1){
			perror("--main: write Error");
			exit(1);
		}
		if(read(STDIN_FILENO, input_buffer, MAX_BF) ==-1){
			perror("Read Error");
			exit(1);
		} 
		//split on pipes
		commands[ncmds] = strtok(input_buffer, "|");
		while(commands[ncmds] != NULL){
			commands[++ncmds] = strtok(NULL, "|");
		}

		if(ncmds > 1){
			//launch in pipe
			execute_pipe(commands, ncmds);
		}
		else{
			execute_non_pipe(commands);
		}
		//clear mem
	}
	return 0;
}