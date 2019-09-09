#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include "builtins.h"

int cd_fn(char *args[]){
    if (args[1] == NULL) {
        perror("insufficient arg");
        exit(1);
    }
    else{
        if (chdir(args[1]) != 0) {
            perror("chdir not working");
            exit(1);
        }
    }
    return 1;
}
char* pwd_fn(){
    return get_current_dir_name();
}
int exit_fn(char *args[]){
    const char * msg = "Quiting ubash v1";
    //INT sub process
    //To DO
    write(STDOUT_FILENO, msg, sizeof(msg));
    exit(0);
}


