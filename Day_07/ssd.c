#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char *lba[100];

void init(){
    for(int i=0;i<100;i++) lba[i] = "0x00000000";
}

int data_Check(char *data){
    if(strlen(data)!=10) return 0;
    if(data[0]!='0'|| data[1]!='x') return 0;
    for(int i=2;i<strlen(data);i++){
        if((data[i] - 'A' < 0 || data[i] - 'A' > 5) && (data[i] - '0' < 0 || data[i] - '0' >= 10)) {
            return 0;
        }
    }
    return 1;
}

void write(int idx, char *data){
    if(idx<0||idx>100) {
        printf("INVALID COMMAND :\t범위를 확인해주세요.\n");
        return;
    }
    if(!data_Check(data)) {
        printf("INVALID COMMAND :\tData를 확인해주세요.\n");
        return;
    }
    lba[idx] = data;
	FILE *fp=fopen("nand.txt","w");
	for(int i=0;i<100;i++) fprintf(fp, "%s\n", lba[i]);
	printf("[%2d] %s SAVED\n",idx,data);
	fclose(fp);
}

void read(int idx){
    if(idx<0||idx>100) {
        printf("INVALID COMMAND :\t범위를 확인해주세요.\n");
        return;
    }
    FILE *fp=fopen("result.txt","w");
	for(int i=0;i<100;i++) fprintf(fp, "%s\n", lba[i]);
	printf("[%2d] %s\n",idx,lba[idx]);
	fclose(fp);
}

void fullwrite(char *data){
    if(!data_Check(data)) {
        printf("INVALID COMMAND :\tData를 확인해주세요.\n");
        return;
    }
    for(int i=0;i<100;i++){
        write(i,data);
    }
}

void fullread(){
    for(int i=0;i<100;i++) read(i);
}

void testapp1(){
    fullwrite("0xAAAAAAAA");
    fullread();
}

void testapp2(){
    for(int i=0;i<30;i++){
        printf("%d\n",i+1);
        for(int j=0;j<6;j++) write(j,"0xAAAABBBB");
    }
    for(int i=0;i<6;i++) write(i,"0x12345678");
    for(int i=0;i<6;i++) read(i);
}

int main(){
    char cmd[255];
    init();
    while(1){
        printf("SSD 명령어 입력 >> ");
        fgets(cmd,255,stdin);
        cmd[strlen(cmd)-1] = '\0';
        if(!strcmp(cmd,"\0")) continue;
        char *buf = strtok(cmd," ");
        // write
        if(!strcmp(buf,"write")){
            buf = strtok(NULL," ");
            if(buf==NULL) {
                printf("INVALID COMMAND\n");
                continue;
            }
            int idx = atoi(buf);
            buf = strtok(NULL," ");
            if(buf==NULL) {
                printf("INVALID COMMAND\n");
                continue;
            }
            char *data = buf;
            buf = strtok(NULL," ");
            if(buf!=NULL){
                printf("INVALID COMMAND\n");
                continue;
            }
            printf("write\n");
            write(idx,data);
        }
        // read
        else if(!strcmp(buf,"read")){
            buf = strtok(NULL," ");
            if(buf==NULL) {
                printf("INVALID COMMAND\n");
                continue;
            }
            int idx = atoi(buf);
            buf = strtok(NULL," ");
            if(buf!=NULL){
                printf("INVALID COMMAND\n");
                continue;
            }
            printf("read\n");
            read(idx);
        }
        // exit
        else if(!strcmp(buf,"exit")) {
            printf("Shell 종료\n");
            break;
        }
        // help
        else if(!strcmp(buf,"help")) {
            printf("\t============================= help =============================\n");
            printf("\twrite      : LBA에 DATA를 저장\tex) write 3 0xAAAABBBB\n");
            printf("\tread       : LBA 읽기\tex) read 3\n");
            printf("\texit       : 종료\n");
            printf("\tfullwrite  : 모든 LBA에 DATA를 저장\tex) fullwrite 0xABCDFFF\n");
            printf("\tfullread   : 모든 LBA 값 출력\tex) fullread\n");
            printf("\tTEST       : testapp1, testapp2\n");
            printf("\t================================================================\n");
        }
        // fullwrite
        else if(!strcmp(buf,"fullwrite")) {
            buf = strtok(NULL," ");
            if(buf==NULL) {
                printf("INVALID COMMAND\n");
                continue;
            }
            char *data = buf;
            buf = strtok(NULL," ");
            if(buf!=NULL){
                printf("INVALID COMMAND\n");
                continue;
            }
            printf("fullwrite\n");
            fullwrite(data);
        }
        // fullread
        else if(!strcmp(buf,"fullread")) {
            printf("fullread\n");
            fullread();
        }
        // TestApp1
        else if(!strcmp(buf,"testapp1")) {
            printf("testapp1\n");
            testapp1();
        }
        // TestApp2
        else if(!strcmp(buf,"testapp2")) {
            printf("testapp2\n");
            testapp2();
        }
        else printf("INVALID COMMAND\n");
   }
}