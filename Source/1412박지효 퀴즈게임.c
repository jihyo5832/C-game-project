#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <conio.h>
#include <mmsystem.h>

#define MAX_X 49
#define MAX_Y 26

#pragma comment(lib, "winmm.lib")

//플레이어
typedef struct Player {
	char name[30];
	int score;
} Player;

//콘솔크기설정
void resizeConsole(void) {
	char chTemp[50];
	sprintf(chTemp, "Mode con cols=%d lines=%d", MAX_X, MAX_Y);
	system(chTemp);
}

//좌표이동
void gotoxy(int x, int y) {
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

//커서지우기
void initCursor(void) {
	CONSOLE_CURSOR_INFO info = { 0 };
	info.dwSize = 1;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}

//시작화면
void displayStartscreen(void) {
	char ch;
	while (1) {
		gotoxy(10, MAX_Y / 2);
		printf("시작하려면 아무키나 누르세요!");
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

//퀴즈1
void Quiz1(Player* p) {
	gotoxy(2, 2);
	puts("Q1. 최고차항의 계수가 1이고, f(0) = 3, f'(3)<0인 사차함수 f(x)가 있다. 실수 t에 대하여 집합 S를 S = {a | 함수 |f(x)-t|가 x = a에서 미분가능하지 않다.}라 하고, 집합 S의 원소의 개수를 g(t)라 하자. 함수 g(t)가 t=3과 t=19에서만 불연속일 때, f(-2)의 값을 구하시오.");
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
		printf("다시 입력하세용ㅎㅎ.");
		goto Choose;
	}
}

//퀴즈2
void Quiz2(Player* p) {
	gotoxy(2, 2);
	puts("Q2. 조민수는 누구인가");
	gotoxy(2, MAX_Y - 3);
	puts("<1> 부산 촌놈");
	gotoxy(2, MAX_Y - 1);
	puts("<2> 동탄 신도시의 품격있는 주민");
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
		printf("다시 입력하세용ㅎㅎ.");
		goto Choose;
	}
}

//퀴즈3
void Quiz3(Player* p) {
	gotoxy(2, 2);
	puts("Q3. x>a에서 정의된 함수 f(x)와 최고차항의 계수가 -1인 사차함수 g(x)가 다음 조건을 만족시킨다. (단, a는 상수이다.)");
	puts("(가) x>a인 모든 실수 x에 대하여 (x-a)f(x) = g(x)이다.");
	puts("(나) 서로 다른 두 실수 a, b에 대하여 함수 f(x)는 x=a와 x=b에서 동일한 극댓값 M을 갖는다. (단, M>0)");
	puts("(다) 함수 f(x)가 극대 또는 극소가 되는 x의 개수는 힘수 g(x)가 극대 또는 극소가 되는 x의 개수보다 많다.");
	puts("b-a=6√3일 때, M의 최솟값을 구하시오.");
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
		printf("다시 입력하세용ㅎㅎ.");
		goto Choose;
	}
}

//화면지우기
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
	PlaySound(TEXT("quiz!.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);		//음악 재생
	initCursor();
	displayStartscreen();
	Player a;
	clock_t start, end;	//시간 측정을 위한 변수
Start:
	gotoxy(0, 0);
	puts("플레이어 이름을 입력하시오");
	gets(a.name);		//플레이어 이름 입력
	eraseScreen();
	a.score = 0;		//점수 초기화
	start = clock();		//시작시간 측정
	Quiz1(&a);
	eraseScreen();
	Quiz2(&a);
	eraseScreen();
	Quiz3(&a);
	eraseScreen();
	end = clock();		//종료사건 축정
	gotoxy(2, MAX_Y / 2 - 2);		
	printf("플레이어 : %s", a.name);
	gotoxy(2, MAX_Y / 2 - 1);
	printf("총점 : %d점", a.score);		//결과 출력
	gotoxy(2, MAX_Y / 2);
	puts("1 : 다시하기   |   2 : 종료");
	gotoxy(2, MAX_Y / 2 + 1);
	printf("총 소모시간 : %.2lf초\n", ((double)end - start)/1000);		//시간 출력
	char k, k1;
Choose:
	k = getchar();
	k1 = getchar();
	switch (k) {
	case '1':		//다시하기
		eraseScreen();
		goto Start;
	case '2':		//종료하기
		eraseScreen();
		return 0;
	default:
		printf("다시 입력하세용ㅎㅎ.");
		goto Choose;
	}
}