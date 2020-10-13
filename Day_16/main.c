#include <stdio.h>
#include <pthread.h>
#include <malloc.h>
#include <string.h>

pthread_mutex_t mlock;
pthread_t tid[100];
int money;
int t;
int exitflag[100];

struct Node
{
	int chn;
	struct Node *next;
};

struct Node *head;
struct Node *last;

void push(int chn)
{
	if (head == NULL) {
		head = (struct Node *)malloc(sizeof(struct Node));
		head->chn = chn;
		head->next = NULL;
		last = head;
		return;
	}

	last->next = (struct Node *)malloc(sizeof(struct Node));
	last = last->next;
	last->chn = chn;
	last->next = NULL;
}

int front()
{
	return head->chn;
}

int pop()
{
	struct Node *temp = head;
	head = head->next;
	free(temp);
}

void run(void *arg)
{
	int x = *(int*)arg;
	while (1)
	{
		if (exitflag[x]) break;
		//critical section
		pthread_mutex_lock(&mlock);
		money++;
		pthread_mutex_unlock(&mlock);
		//
		usleep(100 * 1000);
	}
}

void add()
{
	int temp = t;
	push(temp);
	pthread_create(&tid[t], NULL, run, &temp);
	t++;
}

void del()
{
	int temp = front();
	if (head == NULL) { printf("Empty\n"); return;}
	exitflag[temp] = 1;
	pop();
	pthread_join(tid[temp],NULL);
}

void init()
{
	pthread_mutex_init(&mlock, NULL);
	add();
}

int main()
{
	char prompt[10] = "TShell > ";
	char buf[100];

	init();

	while (1)
	{
		printf("%s", prompt);
		scanf("%s", buf);

		if (!strcmp(buf, "exit") || !strcmp(buf, "quit")) break;

		if (!strcmp(buf, "show")) {
			printf("money = %d\n", money);
		}

		if (!strcmp(buf, "add")) {
			add();
		}

		if (!strcmp(buf, "del")) {
			del();
		}
	}
	for (int i = 0; i < t; i++) {
                if(exitflag[i]) continue;
		pthread_join(tid[i], NULL);
	}
	pthread_mutex_destroy(&mlock);
}
