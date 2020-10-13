#include <stdio.h>
#include <malloc.h>
#include <pthread.h>

typedef struct _node{
   char x;
   struct _node *next;
}node;

node *head;
node *last;

int q_size, end_flag;

void push(char ch){
   q_size++;
   if(head==NULL){
      head = (node*)malloc(sizeof(node));
      head->x = ch;
      head->next = NULL;
      last = head;
      return;
   }
   last->next = (node*)malloc(sizeof(node));
   last = last->next;
   last->x = ch;
   last->next = NULL;
}

void pop(){
   node *p = head;
   head = head->next;
   free(p);
   q_size--;
}

char front() {
   return head->x;
}

void print(){
   while(1){
      usleep(100*1000);
      if(!q_size) {
         if(end_flag==2) return;
         printf("Queue is Empty\n"); 
         continue;
      } 
      printf("PRINT : %c\n",front());
      pop();
   }
}

void TextRead(void *arg){
   char *ch = (char *)arg;
   FILE *fp = fopen(ch,"r");
   char buf[100];
   fscanf(fp, "%s", buf);
   fclose(fp);
   for(int i=0;buf[i];i++){
      while(q_size>=10); // block
      printf("PUSH : %c\n", buf[i]);
      push(buf[i]);
      usleep(100*1000);
   }
   end_flag++;
}

int main(){
   char *f1 = "./A.txt";
   char *f2 = "./B.txt";
   pthread_t t_text1, t_text2, t_print;
   pthread_create(&t_print, NULL, print, NULL);
   pthread_create(&t_text1, NULL, TextRead, (void*)f1);
   pthread_create(&t_text2, NULL, TextRead, (void*)f2);
   
   pthread_join(t_text1,NULL);
   pthread_join(t_text2,NULL);
   pthread_join(t_print,NULL);

   return 0;
}