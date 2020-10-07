#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <Windows.h>
int r[4];

void init() {
	FILE *fp;
	//PC.txt 생성
	printf("PC Register (R15) 를 생성합니다.\n");
	fp = fopen("PC.txt", "w");
	fprintf(fp,"0");
	fclose(fp);
	//IR.txt 생성
	printf("Instruction Register 를 생성합니다.\n");
	fp = fopen("IR.txt", "w");
	fclose(fp);
	//R7.txt 생성
	printf("작업용 Register 를 생성합니다.\n");
	fp = fopen("R7.txt", "w");
	fclose(fp);
}

int Fetch() {
	FILE *fp;
	int line;
	char buf[255];
	//PC.txt 파일 읽고 Line 저장
	fp = fopen("PC.txt", "r");
	fscanf(fp, "%d", &line);
	fclose(fp);
	//PC.txt 숫자 증가
	remove("PC.txt");
	fp = fopen("PC.txt", "w");
	fprintf(fp,"%d",line+1);
	fclose(fp);
	//Assem code Line번째 읽기
	int line_cnt = 0, flag = 0;
	fp = fopen("Assem.txt", "r");
	while (fgets(buf, 255, fp) != NULL) {
		if (line_cnt == line) {
			flag = 1;
			break;
		}
		line_cnt++;
	}
	if(!flag) return 1; // Line이 끝나면 die	
	//printf("%s\n", buf);
	fclose(fp);
	//Assem code를 IR.txt에 저장
	remove("IR.txt");
	fp = fopen("IR.txt", "w");
	fprintf(fp, "%s", buf);
	fclose(fp);
	return 0;
}

void Print(char buf[255]) {
	//Print
	//printf("Print\n%s\n",buf);
	//=> R7.txt 파싱하여 저장 ex) Print #123 => 123 저장 Print r0 => 53 (r0이 53이였다면)
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
	//=> ex Mov r0, #31 => r0 31 Move r0,r3 -=> r0 77 (r3가 77이였다면)
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
	//IR.txt를 읽기
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
	// 각 단계마다 처리 후 0.1 초단 대기를 걸어줌
	// 현재 단계를 출력
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