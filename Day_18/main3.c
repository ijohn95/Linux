#include <stdio.h>
#include <pthread.h>
#include <string.h>
pthread_t t_id[20];
int thread_state[20];
char thread_message[20][100];
int t;

void print(void *arg){
	int idx = *(int*)arg;
	while(1){
		if(thread_state[idx]){
			for(int i=0;thread_message[idx][i];i++){
				printf("%c\n",thread_message[idx][i]);
				usleep(100*1000);
			}
			thread_state[idx] = 0;
		}
		usleep(1000);
	}
}

void thread_pool_init(){
	int idx[20];
	for(int i=0;i<20;i++){
		idx[i] = i;
		pthread_create(&t_id[i],NULL,print,&idx[i]);
	}
}

int main(){
	thread_pool_init();
	char buf[100];
	while(1){
		printf("Test Shell >> ");
		fgets(thread_message[t], 100, stdin);
		thread_state[t] = 1;
		while(thread_state[t]);
		t++;
		if(t==20) break;
	}
	for(int i=0;i<20;i++){
		pthread_join(t_id[i],NULL);
	}
	return 0;
}