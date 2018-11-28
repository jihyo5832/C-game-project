#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <conio.h>
#include <mmsystem.h>

#define MAX_X 49
#define MAX_Y 26

#pragma comment(lib, "winmm.lib")

//�÷��̾�
typedef struct Player {
	char name[30];
	int score;
} Player;

//�ܼ�ũ�⼳��
void resizeConsole(void) {
	char chTemp[50];
	sprintf(chTemp, "Mode con cols=%d lines=%d", MAX_X, MAX_Y);
	system(chTemp);
}

//��ǥ�̵�
void gotoxy(int x, int y) {
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

//Ŀ�������
void initCursor(void) {
	CONSOLE_CURSOR_INFO info = { 0 };
	info.dwSize = 1;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}

//����ȭ��
void displayStartscreen(void) {
	char ch;
	while (1) {
		gotoxy(10, MAX_Y / 2);
		printf("�����Ϸ��� �ƹ�Ű�� ��������!");
		Sleep(300);
		if (_kbhit()) {
			ch = _getch();
			break;
		}
		gotoxy(10, MAX_Y / 2);
		printf("                                    ");
		Sleep(300);
	}
	system("cls");
}

//����1
void Quiz1(Player* p) {
	gotoxy(2, 2);
	puts("Q1. �ְ������� ����� 1�̰�, f(0) = 3, f'(3)<0�� �����Լ� f(x)�� �ִ�. �Ǽ� t�� ���Ͽ� ���� S�� S = {a | �Լ� |f(x)-t|�� x = a���� �̺а������� �ʴ�.}�� �ϰ�, ���� S�� ������ ������ g(t)�� ����. �Լ� g(t)�� t=3�� t=19������ �ҿ����� ��, f(-2)�� ���� ���Ͻÿ�.");
	gotoxy(2, MAX_Y - 3);
	puts("<1> 93");
	gotoxy(2, MAX_Y - 1);
	puts("<2> 147");
	char k,k1;
Choose:
	k = getchar();
	k1 = getchar();
	switch (k) {
	case '2':
		p->score++;
		return;
	case '1':
		return;
	default:
		printf("�ٽ� �Է��ϼ��뤾��.");
		goto Choose;
	}
}

//����2
void Quiz2(Player* p) {
	gotoxy(2, 2);
	puts("Q2. ���μ��� �����ΰ�");
	gotoxy(2, MAX_Y - 3);
	puts("<1> �λ� �̳�");
	gotoxy(2, MAX_Y - 1);
	puts("<2> ��ź �ŵ����� ǰ���ִ� �ֹ�");
	char k, k1;
Choose:
	k = getchar();
	k1 = getchar();
	switch (k) {
	case '1':
		p->score++;
		return;
	case '2':
		return;
	default:
		printf("�ٽ� �Է��ϼ��뤾��.");
		goto Choose;
	}
}

//����3
void Quiz3(Player* p) {
	gotoxy(2, 2);
	puts("Q3. x>a���� ���ǵ� �Լ� f(x)�� �ְ������� ����� -1�� �����Լ� g(x)�� ���� ������ ������Ų��. (��, a�� ����̴�.)");
	puts("(��) x>a�� ��� �Ǽ� x�� ���Ͽ� (x-a)f(x) = g(x)�̴�.");
	puts("(��) ���� �ٸ� �� �Ǽ� a, b�� ���Ͽ� �Լ� f(x)�� x=a�� x=b���� ������ �ش� M�� ���´�. (��, M>0)");
	puts("(��) �Լ� f(x)�� �ش� �Ǵ� �ؼҰ� �Ǵ� x�� ������ ���� g(x)�� �ش� �Ǵ� �ؼҰ� �Ǵ� x�� �������� ����.");
	puts("b-a=6��3�� ��, M�� �ּڰ��� ���Ͻÿ�.");
	gotoxy(2, MAX_Y - 3);
	puts("<1> 216");
	gotoxy(2, MAX_Y - 1);
	puts("<2> 222");
	char k, k1;
Choose:
	k = getchar();
	k1 = getchar();
	switch (k) {
	case '1':
		p->score++;
		return;
	case '2':
		return;
	default:
		printf("�ٽ� �Է��ϼ��뤾��.");
		goto Choose;
	}
}

//ȭ�������
void eraseScreen(void) {
	for (int y = 0; y < MAX_Y; y++) {
		for (int x = 0; x < MAX_X; x++) {
			printf(" ");
		}
		puts("");
	}
}

//=================================================================//

int main(void) {
	resizeConsole();
	PlaySound(TEXT("quiz!.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);		//���� ���
	initCursor();
	displayStartscreen();
	Player a;
	clock_t start, end;	//�ð� ������ ���� ����
Start:
	gotoxy(0, 0);
	puts("�÷��̾� �̸��� �Է��Ͻÿ�");
	gets(a.name);		//�÷��̾� �̸� �Է�
	eraseScreen();
	a.score = 0;		//���� �ʱ�ȭ
	start = clock();		//���۽ð� ����
	Quiz1(&a);
	eraseScreen();
	Quiz2(&a);
	eraseScreen();
	Quiz3(&a);
	eraseScreen();
	end = clock();		//������ ����
	gotoxy(2, MAX_Y / 2 - 2);		
	printf("�÷��̾� : %s", a.name);
	gotoxy(2, MAX_Y / 2 - 1);
	printf("���� : %d��", a.score);		//��� ���
	gotoxy(2, MAX_Y / 2);
	puts("1 : �ٽ��ϱ�   |   2 : ����");
	gotoxy(2, MAX_Y / 2 + 1);
	printf("�� �Ҹ�ð� : %.2lf��\n", ((double)end - start)/1000);		//�ð� ���
	char k, k1;
Choose:
	k = getchar();
	k1 = getchar();
	switch (k) {
	case '1':		//�ٽ��ϱ�
		eraseScreen();
		goto Start;
	case '2':		//�����ϱ�
		eraseScreen();
		return 0;
	default:
		printf("�ٽ� �Է��ϼ��뤾��.");
		goto Choose;
	}
}