#include <stdio.h>
#include <stdlib.h>
#include <string.h>

float calCPU(){
    system("cat /proc/stat > cpuinfo.txt");
    FILE *fp = fopen("cpuinfo.txt","r");
    char buf[255];
    fgets(buf,255,fp);
    //printf("%s",buf);
    char *token; 
    int cpu[4];
    token = strtok(buf," ");
    for(int i=0;i<4;i++){
        token = strtok(NULL," ");
        cpu[i] = atoi(token);
        //printf("%d\n",cpu[i]);
    }
    return (float)(cpu[0]+cpu[1]+cpu[2]) / (float)(cpu[0]+cpu[1]+cpu[2]+cpu[3]); 
} 

float calMEM(){
    system("cat /proc/meminfo > meminfo.txt");
    FILE *fp = fopen("meminfo.txt","r");
    char memtotal[255];
    char memfree[255];
    fgets(memtotal,255,fp);
    fgets(memfree,255,fp);
    //printf("%s",memtotal);
    //printf("%s",memfree);
    char *token;
    token = strtok(memtotal," ");
    token = strtok(NULL," ");
    float m_total = (float)atoi(token);
    token = strtok(memfree," ");
    token = strtok(NULL," ");
    float m_free = (float)atoi(token);
    return (m_total-m_free)/m_total;
}

int calDISK(){
    system("df > disk.txt");
    FILE *fp = fopen("disk.txt","r");
    char buf[255];
    char diskUseage[255];
    while(1){
        char *p = fgets(buf,255,fp);
        if(strstr(p,"/dev/sda1") != NULL){
            strcpy(diskUseage,buf);
            break;
        }
    }
    char *token;
    token = strtok(diskUseage," ");
    token = strtok(NULL," ");
    token = strtok(NULL," ");
    token = strtok(NULL," ");
    token = strtok(NULL," ");
    return (token[0]-'0')*10 + (token[1]-'0');
}

void print_graph(int num){
    printf("[");
    for(int i=0;i<num;i++)
        printf("|");
    for(int i=num;i<100;i++){
        printf(" ");
    }
    printf("] %d%%\n",num);
}

int main(){
    while(1){
        system("figlet CTOP");
        //printf("%f\n%f\n%d\n",calCPU(),calMEM(),calDISK());
        // cpu
        printf("CPU\n");
        print_graph((int)(calCPU()*100));
        // mem
        printf("MEMORY\n");
        print_graph((int)(calMEM()*100));
        // disk
        printf("DISK\n");
        print_graph(calDISK());
        system("sleep 1 && clear");
    }
    return 0;
}