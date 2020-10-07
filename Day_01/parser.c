#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(){	
	FILE *fp = fopen("test.txt","r");
	char buf[255];
	char buf2[255];
	system("dmesg > test.txt");

	while(1){
		char *p = fgets(buf, 255, fp);
		if(p == NULL) break;
		char *ptr = strstr(buf, "sd");
		if(ptr != NULL){
			strcpy(buf2, buf);
			char* result = strtok(buf2,"]");
			if(result != NULL){
				int len = strlen(result);
				int temp = result[len-1] - '0';
				if(temp%2==0){
					printf("%s",buf);
				}
			}
		}
	}
	return 0;
}
