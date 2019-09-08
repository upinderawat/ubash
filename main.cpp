#include <bits/stdc++.h>
#include <unistd.h>//for read(), STDIN_FILENO
#include <string.h>
#include "utils.h"
#include "execute_cmd.h"
#define MAX_BF 10000
#define MAX_CMD 10
using namespace std;

int main(int argc, char const *argv[]){
	//load config files
	char input_buffer[MAX_BF];
	if(read(STDIN_FILENO, input_buffer, MAX_BF) ==-1) perror("Read Error");
	//tokenize
	char * commands[MAX_CMD];
	int i=0;
	commands[i] = strtok(input_buffer, "|");
	while(commands[i] != NULL){
		commands[++i] = strtok(NULL, "|");
	}
	if(i > 1){
		//launch in pipe
	}
	else{
		for (int j = 0; j < i; ++j){
			printf("%s\n", trim(commands[j]));
			char* tokens[MAX_CMD];
			int k=0;
			tokens[k] = strtok(commands[j], " ");
			while(tokens[k] != NULL){
				tokens[++k] = strtok(NULL, " ");
			}
			// for(int l = 0; l< k; l++){
			// 	printf("%d. %s\n", l, trim(tokens[l]));
			// }
			execute_cmd(tokens[0],tokens);
		}		
	}

	return 0;
}