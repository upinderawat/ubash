#include <bits/stdc++.h>
#include <unistd.h>//for read(), STDIN_FILENO
#include <string.h>
#include "utils.h"
#include "execute_cmd.h"
#include <sys/types.h>//pid_t
#include <sys/wait.h>//wait_pid
#define MAX_BF 1000
#define MAX_CMD 50
using namespace std;

int main(int argc, char const *argv[]){
	//load config files
	const char ps1 []= "$: ";
	char* input_buffer;
	char* commands[MAX_CMD];
	char* tokens[MAX_CMD];
	int wstatus;
	int ntokens;
	int ncmds;

	pid_t child_pid;
	
	while(true){
		ntokens = ncmds =0;
		input_buffer = (char *)malloc(MAX_BF);
		if(write(STDOUT_FILENO, ps1, sizeof(ps1)-1)==-1){
			perror("write Error");
			exit(1);
		}
		if(read(STDIN_FILENO, input_buffer, MAX_BF) ==-1){
			perror("Read Error");
			exit(1);
		} 
		commands[ncmds] = strtok(input_buffer, "|");
		while(commands[ncmds] != NULL){
			commands[++ncmds] = strtok(NULL, "|");
		}
		if(ncmds > 1){
			//launch in pipe
			
			execute_pipe()
		}
		else{
			commands[0] = trim(commands[0]);
			ntokens = tokenize(commands[0], tokens);
			if((child_pid = fork())==0){
				execute_cmd(tokens[0],tokens);
			}
			else{
				do{
					waitpid(child_pid, &wstatus, WUNTRACED);
			 	}while (!WIFEXITED(wstatus) && !WIFSIGNALED(wstatus));
			}
		}
	}
	return 0;
}