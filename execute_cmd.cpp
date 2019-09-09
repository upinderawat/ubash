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
// Currently, two type of commands are supported
// 1. execute_pipe
// 2. execute_non_pipe
//

//execute a instruction, first check against all builtins
void execute_cmd(char *file, char *argv[]){
	// if builtin
	if (strcmp(argv[0], "cd") == 0) {
		cd_fn(argv);
		return ;
	}
	else if(strcmp(argv[0],"pwd")==0){
		char * pwd_s = trim(pwd_fn());
		printf("%s", pwd_s);
		return;
		// if(write(STDOUT_FILENO, pwd_s, MAX_BF)==-1){
		// 	perror("--execute_cmd: write Error");
		// 	exit(1);
		// }
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
	if(ntokens <= 0)//if empty command is executed
		return;
//	fprintf(stderr,"Number of tokens = %d\n", ntokens);
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
	int i;
	// printf("Number of commands: %d\n", ncmds);
	int fd0, fd1;
	fd0= STDIN_FILENO;
	for(i=0; i<ncmds; i++){
		commands[i] = trim(commands[i]);
		ntokens = tokenize(commands[i], tokens);
		int p[2];
		if(i < ncmds-1){
			pipe(p);
			fd1=p[1];
		}
		else{
			fd1 = STDOUT_FILENO;
		}
		// printf("Command %d: %s\n",i, commands[i]);
		// printf("Number of tokens: %d\n", ntokens);
		// for(int j=0; j<ntokens; j++){
		// 	printf("\tToken %d: %s\n",j, tokens[j] );
		// }

		if((child_pid = fork())==0){
			if(fd0 != STDIN_FILENO){
				dup2(fd0, STDIN_FILENO);
				close(fd0);
			}
			if(fd1 != STDOUT_FILENO){
				dup2(fd1, STDOUT_FILENO);
				close(fd1);
			}
			execute_cmd(tokens[0], tokens);
		}
		if(fd0 != STDIN_FILENO) close(fd0);
		if(fd1 != STDOUT_FILENO) close(fd1);
		fd0 = p[0];
	}
	wait(NULL);

	// dup2(1, STDOUT_FILENO);
	//execute_cmd(tokens[i], tokens);
	//abort();
}