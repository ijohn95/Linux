#include <stdio.h>
#include <malloc.h>
#include <pthread.h>

typedef struct _node {
	char x;
	struct _node *next;
} node;

node *head[3];
node *last[3];
int q_size[3];
int exit_flag;

void push(char ch, int idx){
	q_size[idx]++;
	if(head[idx] == NULL){
		head[idx] = (node *)malloc(sizeof(node));
		head[idx]->x = ch;
		head[idx]->next = NULL;
		last[idx] = head[idx];
		return;
	}
	last[idx]->next = (node *)malloc(sizeof(node));
	last[idx] = last[idx]->next;
	last[idx]->x = ch;
	last[idx]->next = NULL;
}

void pop(int idx){
	node *p = head[idx];
	head[idx] = head[idx]->next;
	free(p);
	q_size[idx]--;
}

char front(int idx){
	return head[idx]->x;
}

void task1(){
	while(!exit_flag){
		if(q_size[0]==0) {
			usleep(1000);
			continue;
		}
		char ch = front(0);
		pop(0);
		ch -= 32;
		usleep(300*1000);
		push(ch, 1);
	}
}

void task2(){
	while(!exit_flag){
		if(q_size[1]<2){
			usleep(1000);
			continue;
		}
		char ch1 = front(1);
		pop(1);
		char ch2 = front(1);
		pop(1);
		char temp;
		if(ch1>ch2) temp = ch1;
		else temp = ch2;  
		usleep(100*1000);
		push(temp,2);
	}
}

void task3(){
	while(!exit_flag){
		if(q_size[2]==0){
			usleep(1000);
			continue;
		}
		char ch = front(2);
		pop(2);
		printf("[PRINT : %c]\n",ch);
		usleep(100*1000);
		if(!q_size[0] && !q_size[1] && !q_size[2]) {
			exit_flag = 1;
		}
	}
}

int main(){
	pthread_t t_id[3];
	char *str = "abcdefghijklmnopqrstuvwxyz";
	void (*task[3])(void)= {task1,task2,task3};
	for(int i=0;i<3;i++){
		pthread_create(&t_id[i],NULL,task[i],NULL);
	}
	
	for(int i=0;str[i];i++){
		push(str[i], 0);
		usleep(100);
	}

	for(int i=0;i<3;i++){
		pthread_join(t_id[i],NULL);
	}
	return 0;
}