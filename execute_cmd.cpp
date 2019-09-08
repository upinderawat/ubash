#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>//pid_t
#include <sys/wait.h>//wait_pid
#include "execute_cmd.h"
#include "utils.h"
#include "builtins.h"
#define MAX_CMD 50
#define MAX_BF 1000

void execute_cmd(char *file, char *argv[]){
	// if builtin
	if (strcmp(argv[0], "cd") == 0) {
		cd_fn(argv);
		return ;
	}
	else if(strcmp(argv[0],"pwd")==0){
		if(write(STDOUT_FILENO, pwd_fn(), MAX_BF)==-1){
			perror("--execute_cmd: write Error");
			exit(1);
		}
	}
	else if(strcmp(argv[0], "exit")==0){
		exit_fn(argv);
		return;
	}
	//end of builtins

  	if(execvp(file, argv)==-1){
		perror("Could'nt execute command");
		exit(1);
	}
}
void execute_non_pipe(char* commands[]){
	int wstatus;
	pid_t child_pid;
	int ntokens;
	char* tokens[MAX_CMD];
	commands[0] = trim(commands[0]);
	ntokens = tokenize(commands[0], tokens);
	if((child_pid = fork())==0){
		execute_cmd(tokens[0],tokens);
	}
	else{
		do{
			waitpid(child_pid, &wstatus, WUNTRACED);	
		}
		while (!WIFEXITED(wstatus) && !WIFSIGNALED(wstatus));
	}
}
void execute_pipe(char* commands[], int ncmds){
	int wstatus;
	pid_t child_pid;
	int ntokens;
	char* tokens[MAX_CMD];
	for(int i=0; i<ncmds; i++){
		commands[i] = trim(commands[i]);
		ntokens = tokenize(commands[i], tokens);
		if((child_pid = fork())==0){
			execute_cmd(tokens[i], tokens);
		}
		else{
			do{
				waitpid(child_pid, &wstatus, WUNTRACED);	
			}
			while (!WIFEXITED(wstatus) && !WIFSIGNALED(wstatus));
		}
	}
}