#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <Windows.h>
int r[4];

void init() {
	FILE *fp;
	//PC.txt ����
	printf("PC Register (R15) �� �����մϴ�.\n");
	fp = fopen("PC.txt", "w");
	fprintf(fp,"0");
	fclose(fp);
	//IR.txt ����
	printf("Instruction Register �� �����մϴ�.\n");
	fp = fopen("IR.txt", "w");
	fclose(fp);
	//R7.txt ����
	printf("�۾��� Register �� �����մϴ�.\n");
	fp = fopen("R7.txt", "w");
	fclose(fp);
}

int Fetch() {
	FILE *fp;
	int line;
	char buf[255];
	//PC.txt ���� �а� Line ����
	fp = fopen("PC.txt", "r");
	fscanf(fp, "%d", &line);
	fclose(fp);
	//PC.txt ���� ����
	remove("PC.txt");
	fp = fopen("PC.txt", "w");
	fprintf(fp,"%d",line+1);
	fclose(fp);
	//Assem code Line��° �б�
	int line_cnt = 0, flag = 0;
	fp = fopen("Assem.txt", "r");
	while (fgets(buf, 255, fp) != NULL) {
		if (line_cnt == line) {
			flag = 1;
			break;
		}
		line_cnt++;
	}
	if(!flag) return 1; // Line�� ������ die	
	//printf("%s\n", buf);
	fclose(fp);
	//Assem code�� IR.txt�� ����
	remove("IR.txt");
	fp = fopen("IR.txt", "w");
	fprintf(fp, "%s", buf);
	fclose(fp);
	return 0;
}

void Print(char buf[255]) {
	//Print
	//printf("Print\n%s\n",buf);
	//=> R7.txt �Ľ��Ͽ� ���� ex) Print #123 => 123 ���� Print r0 => 53 (r0�� 53�̿��ٸ�)
	char *p = strtok(buf, " ");
	p = strtok(NULL, " ");
	int r1;
	if (p[0] == 'r') {
		r1 = p[1] - '0';
		r1 = r[r1];
	}
	else sscanf(p, "#%d", &r1);
	printf("Print : %d\n", r1);
	FILE *fp;
	fp = fopen("R7.txt", "w");
	fprintf(fp, "%d", r1);
	fclose(fp);
}

void Mov(char buf[255]) {
	//Mov 
	//printf("Mov\n%s\n", buf);
	//=> ex Mov r0, #31 => r0 31 Move r0,r3 -=> r0 77 (r3�� 77�̿��ٸ�)
	char *p = strtok(buf, " ");
	p = strtok(NULL, " ");
	char *reg = "";
	int r1, r2, num;
	strcpy(p, reg);
	r1 = p[1] - '0';
	p = strtok(NULL, " ");
	if (p[0] == 'r') {
		r2 = p[1] - '0';
		r[r1] = r[r2];
	}
	else {
		sscanf(p, "#%d", &num);
		//printf("%d\n", num);
		r[r1] = num;
	}
	FILE *fp;
	fp = fopen("R7.txt", "w");
	fprintf(fp, "%s %d", reg, r[r1]);
	fclose(fp);
}

void Add(char buf[255]) {
	//Add
	//printf("Add\n%s\n", buf);
	//=> ex) Add r1,r2,#55 => r1 r2 55
	buf[strlen(buf) - 1] = '\0';
	char *p = strtok(buf, " ");
	char *reg = "";
	int r1, num;
	p = strtok(NULL, " ");
	strcpy(p, reg);
	r1 = p[1] - '0';
	int sum = 0;
	while (1) {
		p = strtok(NULL, " ");
		if (p == NULL) break;
		if (p[0] == 'r') {
			num = p[1] - '0';
			num = r[num];
		}
		else {
			sscanf(p, "#%d", &num);
		}
		sum += num;
	}
	r[r1] = sum;
	FILE *fp;
	fp = fopen("R7.txt", "w");
	fprintf(fp, "%s %d", reg, r[r1]);
	fclose(fp);
}

void Decode() {
	FILE *fp;
	char buf[255];
	//IR.txt�� �б�
	fp = fopen("IR.txt", "r");
	fgets(buf,255, fp);
	fclose(fp);
	remove("R7.txt");
	if (buf[0] == 'p') Print(buf);
	else if (buf[0] == 'm') Mov(buf);
	else if (buf[0] == 'a') Add(buf);
}


int main() {
	int init_state = 1;
	int die_state = 0;
	// �� �ܰ踶�� ó�� �� 0.1 �ʴ� ��⸦ �ɾ���
	// ���� �ܰ踦 ���
	while (1) {
		if (init_state) {
			init();
			init_state = 0;
			Sleep(100);
			//system("cls");
		}
		die_state = Fetch();
		if (die_state) break;
		Sleep(100);
		Decode();
		Sleep(100);
	}
	return 0;
}