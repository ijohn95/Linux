#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void CPUread(){
    FILE *fp = fopen("lscpu.txt","r");
	char buf[255];
    char *cpulist[] = {"CPU MHz", "CPU op-mode(s)", "Core(s) per socket"};
	while(1){
		char *p = fgets(buf, 255, fp);
		if(p == NULL) break;
        for(int i=0;i<3;i++){
            char *ptr = strstr(buf,cpulist[i]);
            if(ptr != NULL){
                printf("%s",buf);
            }
        }
	}
}

void MEMread(){
    FILE *fp = fopen("meminfo.txt","r");
    char buf[255];
    char *memlist[] = {"MemTotal","MemFree","MemAvailable"};
    while(1){
		char *p = fgets(buf, 255, fp);
		if(p == NULL) break;
        for(int i=0;i<3;i++){
            char *ptr = strstr(buf,memlist[i]);
            if(ptr != NULL){
                printf("%s",buf);
            }
        }
	}
}

void DISKread(){
    FILE *fp = fopen("diskinfo.txt","r");
    char buf[255];
    while(1){ 
		char *p = fgets(buf, 255, fp);
		if(p == NULL) break;
        char *ptr = strstr(buf,"Host");
        if(ptr != NULL){
            printf("%s",buf);
        }
	}
}

int main(){
    char buf[255];
    while(1){
        system("figlet SSAFY SHELL");
        printf("SSAFY #");
        scanf("%s",buf);
        if(strcmp(buf,"list") == 0){
            printf("cpu\t memory\t disk\t exit\n");
        } else if (strcmp(buf, "cpu")  == 0){
            system("lscpu > lscpu.txt");
            CPUread();
        } else if (strcmp(buf, "memory")  == 0){
            system("cat /proc/meminfo > meminfo.txt");
            MEMread();
        } else if (strcmp(buf,"disk")  == 0){
            system("cat /proc/scsi/scsi > diskinfo.txt");
            DISKread();
        } else if (strcmp(buf,"exit") == 0){
            break;
        } else {
            printf("Error\n");
        }
        system("sleep 1");
        system("clear");
    }
    return 0;
}