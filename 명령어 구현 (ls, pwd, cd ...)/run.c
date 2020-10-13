#include "run.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void ls(){
    system("ls");
}
void cd(char *p){
    if(!strcmp(p,"..")) {
        system("cd .. && pwd");
    } else {
        char cmd[255];
        sprintf(cmd, "cd %s && pwd",p);
        system(cmd);
    } 
}
void pwd(){
    system("pwd");
}

void error(){
    printf("============INVALID COMMAND============\n");
    printf("Command List : exit/quit ls cd pwd cd..\n");
    printf("=======================================\n");
}