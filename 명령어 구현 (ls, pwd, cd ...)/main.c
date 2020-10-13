#include <stdio.h>
#include <string.h>
#include "run.h"
char buf[255];

void Atoa(){
    int l = strlen(buf);
    for(int i=0;i<l;i++){
        if(buf[i] <97 && buf[i]>=65) buf[i]+=32;
    }
}

int main(){
    while(1){
        printf("wontae.choi >> ");
        fgets(buf,255,stdin);
        Atoa();
        buf[strlen(buf)-1] = '\0';
        char* p = strtok(buf," ");
        if(p==NULL) continue;
        if(!strcmp(p,"ls")) {
            p = strtok(NULL," ");
            if(p==NULL) ls();
            else printf("***JUST Type ls***\n");
        }
        else if(!strcmp(p,"cd")) {
            p = strtok(NULL," ");
            if(p==NULL) printf("***Type Directory***\n"); 
            else cd(p);
        }
        else if(!strcmp(p,"pwd")) {
            p = strtok(NULL," ");
            if(p==NULL) pwd();
            else printf("***JUST Type pwd***\n");
        }        
        else if(!strcmp(p,"exit")|| !strcmp(p,"quit")) break;
        else error();
    }
    return 0;
}