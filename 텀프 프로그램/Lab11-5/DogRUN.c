// Dog RUN
// 
// keyboard 방향키↑를 누르면 강아지 점프
// 하트를 먹으면 생명 증가
// 지나가는 block에 부딪히면 생명 감소
// block을 피하는 게임
//
#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include <stdbool.h>
#include <time.h>
#include <mmsystem.h>
#include <process.h>
#pragma comment(lib,"winmm.lib")

// 색상 정의
#define BLACK	0
#define BLUE1	1
#define GREEN1	2
#define CYAN1	3
#define RED1	4
#define MAGENTA1 5
#define YELLOW1	6
#define GRAY1	7
#define GRAY2	8
#define BLUE2	9
#define GREEN2	10
#define CYAN2	11
#define RED2	12
#define MAGENTA2 13
#define YELLOW2	14
#define WHITE	15

#define STAR '*'
#define BLANK ' '

#define ESC 0x1b

#define SPECIAL1 0xe0 // 특수키는 0xe0 + key 값으로 구성된다.
#define SPECIAL2 0x00 // keypad 경우 0x00 + key 로 구성된다.

#define UP  0x48 // Up key는 0xe0 + 0x48 두개의 값이 들어온다.
#define DOWN 0x50
#define LEFT 0x4b
#define RIGHT 0x4d

#define UP2		'w'
#define DOWN2	's'
#define LEFT2	'a'
#define RIGHT2	'd'

#define WIDTH 80
#define HEIGHT 24
int map[HEIGHT][WIDTH] = { 1,0,1,0,1,0,1,0,1 };
int Delay = 50; // 100 msec delay, 이 값을 줄이면 속도가 빨라진다.
int cnt = 0;
int keep_moving;
int sfx_on = 1; // 효과음 On

void removeCursor(void) 
{ // 커서를 안보이게 한다

	CONSOLE_CURSOR_INFO curInfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
	curInfo.bVisible = 0;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
}

void SetConsoleView()
{
	system("mode con:cols=118 lines=26");
	system("title Dog RUN - 2071321 최승재");
}

void gotoxy(int x, int y) //내가 원하는 위치로 커서 이동
{
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);// WIN32API 함수입니다. 이건 알필요 없어요
}

void textcolor(int fg_color, int bg_color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), fg_color | bg_color << 4);
}

// 화면 지우기고 원하는 배경색으로 설정한다.
void cls(int bg_color, int text_color)
{
	char cmd[100];
	system("cls");
	sprintf(cmd, "COLOR %x%x", bg_color, text_color);
	system(cmd);
}

void putdog(int dog_x, int dog_y)
{
	gotoxy(dog_x, dog_y);
	static bool legFlag = true;
	textcolor(MAGENTA1, WHITE);
	printf("　　　　 ∩＿＿_∩\n");
	printf("　　　　 | ノ　　`(つ)\n");
	printf("　　　　/　●　 ●|| ｜\n");
	printf("　 ／＼｜　 (_●_)ミ /\n");
	printf("- ／　彡､　 |∪|ノ/\n");
	printf(" (∪／＼　　  ノ ／\n");
	printf("_￣　 /　　　  ／\n");
	printf("＿＿ ｜　　　  /\n");
	if (legFlag)
	{
		printf("＿＿ ∧　　 ￣￣)\n");
		printf("＿　/　＼＿ /　/\n");
		printf("―／　／　  (　＼\n");
		printf("-/　／　　　＼＿)\n");
		printf("｜ /\n");
		printf("(ノ\n");
		legFlag = false;
	}
	else
	{
		printf("＿＿  |　　   ＼\n");
		printf("＿　  /　/ ＼　＼\n");
		printf("――(___／　 ＼ ＼\n");
		printf(" 　      　   ＼ ＼\n");
		printf("		＼＿)\n");
		legFlag = true;
	}
	textcolor(BLACK, WHITE);
}

void putslidingdog(int dog_x, int dog_y)
{
	gotoxy(dog_x, dog_y);
	static bool legFlag = true;
	textcolor(MAGENTA1, WHITE);
	printf("　　　　 　　　　 　　　　  \n");
	printf("　　　　　　　 　　　　 　　\n");
	printf("　　　　 　　　　 　　　　  \n");
	printf("　       　∩＿＿_∩\n");
	printf("-       　 | ノ　　`(つ)\n");
	printf("        　/　●　 ●|| ｜\n");
	printf("_￣　   /｜　 (_●_)ミ /\n");
	printf("＿＿  ｜彡､　 |∪|ノ/\n");
	if (legFlag)   
	{
		printf("＿＿ ∧　　 ￣￣)\n");
		printf("＿　/　＼＿ /　/\n");
		printf("―／　／　  (　＼\n");
		printf("-/　／　　　＼＿)\n");
		printf("｜ /\n");
		printf("(ノ\n");
		legFlag = false;
	}
	else
	{
		printf("＿＿  |　　   ＼\n");
		printf("＿　  /　/ ＼　＼\n");
		printf("――(___／　 ＼ ＼\n");
		printf(" 　      　   ＼ ＼\n");
		printf("		＼＿)\n");
		legFlag = true;
	}
	textcolor(BLACK, WHITE);
}

void erasedog(int x, int y)
{
	gotoxy(x, y);
	printf("　　　　 　　　　 　　　　  \n");
	printf("　　　　　　　 　　　　 　　\n");
	printf("　　　　 　　　　 　　　　  \n");
	printf("　　　　　　　 　　　　 　　\n");
	printf("　　　　 　　　　 　　　　  \n");
	printf("　　　　　　　 　　　　 　　\n");
	printf("　　　　 　　　　 　　　　  \n");
	printf("　　　　　　　 　　　　 　　\n");
	printf("　　　　 　　　　 　　　　  \n");
	printf("　　　　　　　 　　　　 　　\n");
	printf("　　　　 　　　　 　　　　  \n");
	printf("　　　　　　　 　　　　 　　\n");
	printf("　　　　 　　　　 　　　　  \n");
	printf("　　　　　　　 　　　　 　　\n");
}

void dog_effect(int dog_x,int dog_y)
{
	textcolor(RED2, WHITE);
	gotoxy(dog_x, dog_y);
	static bool legFlag = true;
	printf("　　　　 ∩＿＿_∩\n");
	printf("　　　　 | ノ　　`(つ)\n");
	printf("　　　　/　●　 ●|| ｜\n");
	printf("　 ／＼｜　 (_●_)ミ /\n");
	printf("- ／　彡､　 |∪|ノ/\n");
	printf(" (∪／＼　　  ノ ／\n");
	printf("_￣　 /　　　  ／\n");
	printf("＿＿ ｜　　　  /\n");
	if (legFlag)
	{
		printf("＿＿ ∧　　 ￣￣)\n");
		printf("＿　/　＼＿ /　/\n");
		printf("―／　／　  (　＼\n");
		printf("-/　／　　　＼＿)\n");
		printf("｜ /\n");
		printf("(ノ\n");
		legFlag = false;
	}
	else
	{
		printf("＿＿  |　　   ＼\n");
		printf("＿　  /　/ ＼　＼\n");
		printf("――(___／　 ＼ ＼\n");
		printf(" 　      　   ＼ ＼\n");
		printf("		＼＿)\n");
		legFlag = true;
	}
	textcolor(BLACK, WHITE);
	Sleep(200);
}

// box 그리기 함수, ch 문자열로 (x1,y1) ~ (x2,y2) box를 그린다.
void draw_box(int x1, int y1, int x2, int y2, char ch)
{
	int x, y;
	cls(WHITE, BLACK);
	textcolor(BLUE1, WHITE);
	for (x = x1; x <= x2; x += 2)
	{ // 한글은 2칸씩 차지한다.
		gotoxy(x, y1);
		printf("%s", "─"); // ㅂ 누르고 한자키 누르고 선택
		gotoxy(x, y2);
		printf("%s", "─");
	}

	for (y = y1; y <= y2; y++) 
	{
		gotoxy(x1, y);
		printf("%s", "│");
		gotoxy(x2, y);
		printf("%s", "│");
	}
	gotoxy(x1, y1); printf("┌");
	gotoxy(x1, y2); printf("└");
	gotoxy(x2, y1); printf("┐");
	gotoxy(x2, y2); printf("┘");
	textcolor(BLACK, WHITE);
}

// box 그리기 함수, ch 문자열로 (x1,y1) ~ (x2,y2) box를 그린다.
void draw_box2(int x1, int y1, int x2, int y2, char* ch)
{
	int x, y;
	for (x = x1; x <= x2; x+=2) 
	{
		gotoxy(x, y1);
		printf("%s", "─");
	}
	for (x = x1; x <= x2; x++) 
	{
		textcolor(GREEN1, WHITE);
		gotoxy(x, y2);
		printf("%s", "^");
		textcolor(BLACK, WHITE);
	}
}

void draw_box3(int x1, int y1, int x2, int y2, char* ch)
{
	int x, y;
	for (y = y1; y < y2; y++) 
	{
		gotoxy(x1, y);
		printf("%s", "│");
	}
}

void draw_box4(int x1, int y1, int x2, int y2, char* ch)
{
	int x, y;
	for (y = y1; y < y2; y++)
	{
		gotoxy(x2, y);
		printf("%s", "│");
	}
}

int block_x = 78;
int block_y = 19;

void init_block()
{
	map[block_y][block_x] = 1;
	map[block_y][block_x+2] = 1;
	map[block_y][block_x-2] = 1;
	map[block_y + 1][block_x] = 1;
	map[block_y + 1][block_x+2] = 1;
	map[block_y + 1][block_x-2] = 1;
	map[block_y + 2][block_x] = 1;
	map[block_y + 3][block_x] = 1;
	map[block_y + 4][block_x] = 1;
}

void show_block()
{
	int x, y;
	for (x = 1; x < WIDTH - 1; x++) 
	{
		for (y = 1; y < HEIGHT; y++) 
		{
			if (map[y][x] == 1) 
			{
				gotoxy(x, y);
				textcolor(YELLOW1, WHITE);
				printf("■"); // ㅁ 한자.
				textcolor(BLACK, WHITE);
			}
		}
	}
}

void erase_block()
{
	int x, y;
	for (x = 1; x < WIDTH - 1; x++) 
	{
		for (y = 1; y < HEIGHT; y++) 
		{
			if (map[y][x] == 1)
			{
				gotoxy(x, y);
				printf(" "); // ㅁ 한자.
			}
		}
	}
	map[block_y][block_x] = 0;
	map[block_y][block_x + 2] = 0;
	map[block_y][block_x - 2] = 0;
	map[block_y + 1][block_x] = 0;
	map[block_y + 1][block_x + 2] = 0;
	map[block_y + 1][block_x - 2] = 0;
	map[block_y + 2][block_x] = 0;
	map[block_y + 3][block_x] = 0;
	map[block_y + 4][block_x] = 0;
}

void move_block(dx, dy)
{
	erase_block();
	block_x += dx;
	if (block_x == 0) 
	{
		block_x = WIDTH - 2;
		//if (Delay > 5)
		//	Delay -= 5;
	}
	block_y += dy;
	init_block();
	show_block();
}

void block_effect(int block_x)
{
	gotoxy(block_x-2, block_y);
	printf("~~~~~~~~~~~~");
	gotoxy(block_x-2, block_y + 1);
	printf("~~~~~~~~~~~~");
	gotoxy(block_x, block_y + 2);
	printf("~~~~~~~~~~~~~~");
	gotoxy(block_x, block_y + 3);
	printf("~~~~~~~~~~~~~~");
	gotoxy(block_x, block_y + 4);
	printf("~~~~~~~~~~~~~~");
	Sleep(100);
}

void erase_block_effect(int block_x)
{
	gotoxy(block_x - 2, block_y);
	printf("             ");
	gotoxy(block_x - 2, block_y + 1);
	printf("             ");
	gotoxy(block_x, block_y + 2);
	printf("               ");
	gotoxy(block_x, block_y + 3);
	printf("               ");
	gotoxy(block_x, block_y + 4);
	printf("                ");
	Sleep(100);
}

int heart_x = 68;
int heart_y = 3;

void init_heart() 
{
	static bool heartFlag = true;
	textcolor(RED2, WHITE);
	if (heartFlag) 
	{
		gotoxy(heart_x, heart_y);     printf("   **  **   ");
		gotoxy(heart_x, heart_y + 1); printf("  ********  ");
		gotoxy(heart_x, heart_y + 2); printf("  ********  ");
		gotoxy(heart_x, heart_y + 3); printf("   ******   ");
		gotoxy(heart_x, heart_y + 4); printf("    ****    ");
		gotoxy(heart_x, heart_y + 5); printf("     **     ");
		heartFlag = false;

	}
	else 
	{
		gotoxy(heart_x, heart_y);     printf("   **  **   ");
		gotoxy(heart_x, heart_y + 1); printf("  *  **  *  ");
		gotoxy(heart_x, heart_y + 2); printf("  *      *  ");
		gotoxy(heart_x, heart_y + 3); printf("   *    *   ");
		gotoxy(heart_x, heart_y + 4); printf("    *  *    ");
		gotoxy(heart_x, heart_y + 5); printf("     **     ");
		heartFlag = true;

	}
	//i = i ? 0 : 1;
	textcolor(BLACK, WHITE);

}

void erase_heart()
{
		gotoxy(heart_x, heart_y);     printf("             ");
		gotoxy(heart_x, heart_y + 1); printf("             ");
		gotoxy(heart_x, heart_y + 2); printf("             ");
		gotoxy(heart_x, heart_y + 3); printf("             ");
		gotoxy(heart_x, heart_y + 4); printf("             ");
		gotoxy(heart_x, heart_y + 5); printf("             ");
}

void move_heart(dx, dy)
{
	erase_heart();
	heart_x += dx;
	if (heart_x == 0) 
	{
		heart_x = WIDTH - 12;
	}
	heart_y += dy;
	init_heart();
}

void heart_effect(int heart_x)
{
	textcolor(RED2, WHITE);
	gotoxy(heart_x, heart_y);     printf("　∩＿＿_∩ ");
	gotoxy(heart_x, heart_y + 1); printf("  | ノ 　 `(");
	gotoxy(heart_x, heart_y + 2); printf(" / ♥　  ♥ |");
	gotoxy(heart_x, heart_y + 3); printf(" 　 (_●_)ミ");
	gotoxy(heart_x, heart_y + 4); printf("    |∪|    ");
	gotoxy(heart_x, heart_y + 5); printf("            ");
	textcolor(BLACK, WHITE);
	Sleep(100);
}

int jelly_x = 30;
int jelly_y = 5;

void init_jelly()
{
	textcolor(BLUE1, WHITE);
	gotoxy(jelly_x, jelly_y);     printf("  ****  ");
	gotoxy(jelly_x, jelly_y + 1); printf("  ****  ");
	gotoxy(jelly_x, jelly_y + 2); printf("  ****  ");
	textcolor(BLACK, WHITE);
}

void erase_jelly()
{
	gotoxy(jelly_x, jelly_y - 2); printf("             ");
	gotoxy(jelly_x, jelly_y - 1); printf("             ");
	gotoxy(jelly_x, jelly_y);     printf("             ");
	gotoxy(jelly_x, jelly_y + 1); printf("             ");
	gotoxy(jelly_x, jelly_y + 2); printf("             ");
} 

void move_jelly(dx, dy)
{
	erase_jelly();
	jelly_x += dx;
	if (jelly_x == 0)
	{
		jelly_x = WIDTH - 12;
	}
	jelly_x += dy;
	init_jelly();
}

void jelly_effect(int heart_x)
{
	textcolor(BLUE1, WHITE);
	gotoxy(heart_x, heart_y);     printf("　∩＿＿_∩ ");
	gotoxy(heart_x, heart_y + 1); printf("  | ノ 　 `(");
	gotoxy(heart_x, heart_y + 2); printf(" / ★　  ★ |");
	gotoxy(heart_x, heart_y + 3); printf(" 　 (_●_)ミ");
	gotoxy(heart_x, heart_y + 4); printf("    |∪|    ");
	gotoxy(heart_x, heart_y + 5); printf("            ");
	textcolor(BLACK, WHITE);
	Sleep(100);
}

bool crash1(const int block_X, const int dog_y, const int life)
{
	gotoxy(15, 0);
	textcolor(BLUE2, YELLOW2);
	if (life == 4)
		printf("life : ♥♥♥♥", life);
	else if (life == 3)
		printf("life : ♥♥♥♡", life);
	else if (life == 2)
		printf("life : ♥♥♡♡", life);
	else if (life == 1)
		printf("life : ♥♡♡♡", life);
	textcolor(BLACK, WHITE);
	if (block_X <= 6 && block_X > 5 && dog_y > 5)
	{
		return true;
	}
	return false;
}

bool crash2(const int heart_x, const int dog_y, const int life)
{
	gotoxy(15, 0);
	textcolor(BLUE2, YELLOW2);
	if (life == 4)
		printf("life : ♥♥♥♥", life);
	else if (life == 3)
		printf("life : ♥♥♥♡", life);
	else if (life == 2)
		printf("life : ♥♥♡♡", life);
	else if (life == 1)
		printf("life : ♥♡♡♡", life);
	textcolor(BLACK, WHITE);
	if (heart_x <= 6 && heart_x > 5 && dog_y < 8)
	{
		return true;
	}
	return false;
}

bool crash3(const int jelly_x, const int dog_y, const int life)
{
	gotoxy(15, 0);
	if (jelly_x <= 6 && jelly_x > 5  && dog_y < 8 )
	{
		return true;
	}
	return false;
}

void infoDraw() 
{
	while (1) {
		cls(WHITE, BLACK);
		textcolor(GREEN1, WHITE);
		gotoxy(3, 1); 
		printf("[ 게임 설명 ]");
		textcolor(BLACK, WHITE);
		gotoxy(3, 3);  
		printf(" 이 게임은 1인 Play 게임입나다.  ");
		gotoxy(3, 4);  
		printf(" 강아지가 달리면서 다가오는 장애물을 피하며 점수를 획득하는 게임  ");
		gotoxy(32, 5); printf("┌─┐         ┌─┐");
		gotoxy(3, 6);  
		printf(" ① 이동(방향키 이용)  점프 :│↑│ 아래로 :│↓│");
		gotoxy(32, 7); printf("└─┘         └─┘");
		gotoxy(3, 8);  
		printf(" ②  ****  젤리 ->점수 증가  ** **   하트 ->생명 증가");
		textcolor(BLUE1, WHITE);
		gotoxy(6, 8);  printf(" ****  젤리 ");
		gotoxy(6, 9);  printf(" ****          +10");
		gotoxy(6, 10); printf(" **** ");
		textcolor(BLACK, WHITE);
		textcolor(RED1, WHITE);
		gotoxy(30, 8);  printf("  ** **   하트 ");
		gotoxy(30, 9);  printf(" ********         +1");
		gotoxy(30, 10); printf(" ******** ");
		gotoxy(30, 11); printf("  ******  ");
		gotoxy(30, 12); printf("   ****   ");
		gotoxy(30, 13); printf("    **    ");
		textcolor(BLACK, WHITE);
		gotoxy(3, 14); 
		printf(" ③ ■■■ 장애물에 닿으면 생명 감소, 버티는 시간만큼 점수 증가");
		textcolor(YELLOW1, WHITE);
		gotoxy(6, 14); printf(" ■■■ 장애물");
		gotoxy(6, 15); printf(" ■■■                  -1");
		gotoxy(6, 16); printf("   ■");
		gotoxy(6, 17); printf("   ■");
		gotoxy(6, 18); printf("   ■");
		textcolor(BLACK, WHITE);
		gotoxy(3, 19); 
		printf(" ④ 플레이어의 생명이 다 깎이면 게임 오버");
		gotoxy(17, 20); printf("┌──┐");
		gotoxy(3, 21); 
		printf(" ⑤ 게임 도중 │ESC │를 누르면 게임 오버되어 게임을 끝낼 수 있다.");
		gotoxy(17, 22); printf("└──┘");

		textcolor(RED1, WHITE);
		gotoxy(35, 24); 
		printf(" 아무키나 누르면 메인 화면으로 돌아갑니다.");
		textcolor(BLACK, WHITE);
		if (getch())
			break;
	}
}

void infoDraw2()
{
	gotoxy(111, 0);
	printf("┌─┐");
	gotoxy(84, 1);
	printf(" 이동(방향키 이용)   점프 :│↑│");
	gotoxy(111, 2);
	printf("└─┘");
	gotoxy(111, 3);
	printf("┌─┐");
	gotoxy(84, 4);							 
	printf("                   아래로 :│↓│");
	gotoxy(111, 5);
	printf("└─┘");
	textcolor(BLUE1, WHITE);
	gotoxy(84, 6);     printf("   ****  ");
	gotoxy(84, 6 + 1); printf("   ****  ");
	gotoxy(84, 6 + 2); printf("   ****  ");
	textcolor(BLACK, WHITE);
	gotoxy(94, 7);
	printf("   젤리 -> score += 10 ");
	textcolor(RED2, WHITE);
	gotoxy(84, 10);     printf("  ** **   ");
	gotoxy(84, 10 + 1); printf(" ******** ");
	gotoxy(84, 10 + 2); printf(" ******** ");
	gotoxy(84, 10 + 3); printf("  ******  ");
	gotoxy(84, 10 + 4); printf("   ****   ");
	gotoxy(84, 10 + 5); printf("    **    ");
	textcolor(BLACK, WHITE);
	gotoxy(94, 12);
	printf("   하트 -> life ++");
	textcolor(YELLOW1, WHITE);
	gotoxy(84, 16 + 1); printf("  ■■■");
	gotoxy(84, 16 + 2); printf("  ■■■");
	gotoxy(84, 16 + 3); printf("    ■");
	gotoxy(84, 16 + 4); printf("    ■");
	gotoxy(84, 16 + 5); printf("    ■");
	textcolor(BLACK, WHITE);
	gotoxy(94, 19);
	printf("   블록 -> life --");
	gotoxy(84, 23); printf("┌──┐");
	gotoxy(84, 24);
	printf("│ESC │   ->   GAME OVER  ");
	gotoxy(100, 25); printf("(Y: yes, N : no) ");
	gotoxy(84, 25); printf("└──┘");
}

void gameover(int score) 
{
	cls(WHITE, BLACK);
	
	while (1) 
	{
		int c1;
		c1 = rand() % 6;
		textcolor(c1, WHITE);
		gotoxy(22, 5);  
		printf(" ######      ##   ##   ##   ######        #####   ##   ##   ######  ######");
		gotoxy(22, 6);  
		printf("##  ##     #####  ### ###  #######       #######  ##   ##  #######  #######");
		gotoxy(22, 7); 
		printf("##         ## ##  #######  ##            ##   ##  ##   ##  ##       ##   ##");
		gotoxy(22, 8);  
		printf("### ###   ##  ##  #######  #######       ##   ##  ##   ##  #######  ######");
		gotoxy(22, 9);  
		printf("###  ##   ######  ## # ##  ##            ##   ##  ### ###  ##       ##   ##");
		gotoxy(22, 10); 
		printf("###  ##  ##   ##  ##   ##  #######       #######   #####   #######  ##   ##");
		gotoxy(22, 11); 
		printf("#######  ##   ##  ##   ##   ######        #####     ###     ######  ##   ##");
		textcolor(BLACK, WHITE);
		gotoxy(54, 15); printf("score = %d점", score);
		// 점수 구간 별 출력 멘트 변화
		gotoxy(50, 17);
		if (score < 50)
			printf("게임하신 거 맞나요>??");
		else if (score>=50 &&score < 150)
			printf("더욱 분발해보세요!!!");
		else if (score >= 150 && score < 350)
			printf("나쁘지 않은 실력이에요~!!");
		else if (score >= 350 && score < 500)
			printf("꽤 잘하시네요~~~!!??!");
		else if (score >= 500)
			printf("이 게임을 마스터하셨군요~!!!");
		//gotoxy(39, 20);
		//int i = rand() % 2;
		static bool buttonFlag = true;
		if (buttonFlag)
		{
			gotoxy(39, 20);
			printf("**Hit (R) to Restart (M) to Main (Q) to Quit**");
			buttonFlag = false;
		}
		else
		{
			gotoxy(39, 20);
			printf("                                               ");
			buttonFlag = true;
		}
		
		if (kbhit()==1) 
		{
			unsigned char ch;
			ch = getch();
			if (ch == 'r' || ch == 'q' || ch == 'm')
				break;
		}
		Sleep(200);
	}
}

void draw_hline(int y, int x1, int x2, char ch)
{
	gotoxy(x1, y);
	for (; x1 <= x2; x1++)
		putchar(ch);
}

////게임 초기화, 처음 시작과 Restart때 호출
void init_game()
{
	int x, y;
	char cmd[100];

	srand(time(NULL));

	keep_moving = 1;
	Delay = 50;
	cls(WHITE, BLACK);
	removeCursor();
	system(cmd);
	textcolor(BLACK, YELLOW2);
	draw_hline(0, 0, 80, ' ');
	textcolor(BLACK, WHITE);
}

void endDraw() 
{
	cls(WHITE, BLACK);
	draw_box(40, 4, 80, 12, '□');
	gotoxy(43, 8);
	printf(" [ Dog RUN 게임을 종료합니다... ]\n\n");
	/*while(1)
	{
		if (getch())
			break;
	}*/
}

void endMessage()
{
	cls(WHITE, BLACK);
	draw_box(40, 8, 70, 12, '□');
	gotoxy(45, 10);
	printf("게임을 종료하겠습니까?");
	gotoxy(45, 14);
	printf("yes : 'y' ,  NO : 'n'");
	gotoxy(45, 15);
	printf("(게임오버 , 게임 재시작)");
	/*while (1)
	{
		if (getch())
			break;
	}*/
}

void PlayBgm(char* filename) 
{
	int filenameLength = strlen(filename) + 1; // Length including null terminator
	// Calculate the required buffer size for the wide-character string
	int bufferSize = MultiByteToWideChar(CP_UTF8, 0, filename, filenameLength, NULL, 0);
	// Allocate memory for the wide-character string
	TCHAR* wideFilename = (TCHAR*)malloc(bufferSize * sizeof(TCHAR));
	// Convert the char* filename to a TCHAR wide-character string
	MultiByteToWideChar(CP_UTF8, 0, filename, filenameLength, wideFilename, bufferSize);
	PlaySound(NULL, NULL, 0); // 기존에 play중인 bgm stop
	// TEXT() 형식으로 파일명 변경해서 처리해야 함.
	PlaySound(wideFilename, NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
}

HANDLE pipeHandle2;// P1과 통신하기 위한 named pipe
void SendMsg(char* message) 
{
	// Send a message to p1 to change the BGM
	//gotoxy(0, 0); printf("Sending %s", message);
	DWORD bytesWritten;
	WriteFile(pipeHandle2, message, strlen(message), &bytesWritten, NULL);
	if (strcmp(message, "quit") == 0)
		CloseHandle(pipeHandle2);
}

void main(int argc, char* argv[])
{
	SetConsoleView();
	unsigned char ch; // 특수키 0xe0 을 입력받으려면 unsigned char 로 선언해야 함
	int oldx, oldy, newx, newy;

START:

	cls(WHITE, BLACK);
	// 처음 실행할 때는 argc == 1로 시작되고
// 아래에서 spawnl() 으로 자기 자신을 다시 실행하면
// argc == 2 로 내려오기 때문에 이 부분을 pass 한다.
	//if (argc == 1)
	//{
	//	// bgm 재생
	//	PlaySound(TEXT("bgm1.wav"), 0, SND_FILENAME | SND_ASYNC | SND_LOOP);
	//	// 게임 실행하고 게임이 종료될때까지 기다린다.
	//	spawnl(P_WAIT, argv[0], argv[0], "gamerun", NULL);
	//	// 게임이 종료되면 bgm process도 종료
	//	exit(0);
	//}

	if (argc == 1) 
	{ // 새로운 방식, P1 과 P2를 named pipe 로 연결해서 P2가 요청하면 P1이 BGM을 변경한다.
		// Create a named pipe
		HANDLE pipeHandle1 = CreateNamedPipe(
			TEXT("\\\\.\\pipe\\MyPipe"),        // Pipe name
			PIPE_ACCESS_DUPLEX,                 // Read and write access
			PIPE_TYPE_BYTE | PIPE_READMODE_BYTE | PIPE_WAIT,   // Pipe mode
			1,                                  // Number of instances
			0,                                  // Out buffer size
			0,                                  // In buffer size
			0,                                  // Default timeout
			NULL                                // Security attributes
		);
		if (pipeHandle1 == INVALID_HANDLE_VALUE)
		{
			//printf("Failed to create named pipe. Error: %lu\n", GetLastError());
			return 1;
		}
		// P2를 실행시키고 끝날때 까지 기다리지 않는다.
		spawnl(P_NOWAIT, argv[0], argv[0], "gamerun", NULL);
		// Wait for a client to connect
		ConnectNamedPipe(pipeHandle1, NULL);
		// Loop to listen for messages from p2

		while (1) 
		{
			char buffer[256];
			DWORD bytesRead;
			int ret;
			// Read the message from p2
			if ((ret = ReadFile(pipeHandle1, buffer, sizeof(buffer), &bytesRead, NULL))) 
			{
				buffer[bytesRead] = '\0';
				if (strcmp(buffer, "quit") == 0) // P1이 종료되는 경우
					break;
				else if (strcmp(buffer, "no BGM") == 0)
					PlaySound(NULL, 0, 0);// BGM 중지
				else
					PlayBgm(buffer);
			}

			if (ret < 0) 
			{
				gotoxy(0, 0);
				printf("ReadFile error");
				break;
			}
		}
		// Close the named pipe handle
		CloseHandle(pipeHandle1);
		exit(0); // P1 종료
	}
	else 
	{ // P2 process (GAME 실행 담당)
		pipeHandle2 = CreateFile(
			TEXT("\\\\.\\pipe\\MyPipe"),       // Pipe name
			GENERIC_WRITE,       // Read and write access
			0,                                  // No sharing
			NULL,                               // Default security attributes
			OPEN_EXISTING,                      // Open an existing pipe
			0,                                  // Default attributes and flags
			NULL                                // No template file
		);
		if (pipeHandle2 == INVALID_HANDLE_VALUE)
		{
			//printf("Failed to open named pipe. Error: %lu\n", GetLastError());
			//return 1;
		}
	}

	// 메인 화면 실행 법
	gotoxy(0, 21);
	printf("┌   MOVE   ┐ ");
	gotoxy(0, 22);
	printf("   UP : ↑");
	gotoxy(0, 23);
	printf("  DOWN : ↓");
	gotoxy(0, 24);
	printf(" CHOICE : <┘");
	gotoxy(0, 25);
	printf("└          ┘ ");

	// 게임 소리 설정 법
	gotoxy(100, 21);
	printf("┌   SOUND    ┐ ");
	gotoxy(100, 22);
	printf("   BGM ON  : 3");
	SendMsg("no BGM");
	SendMsg("bgm1.wav");
	if (sfx_on == 1)
	{
		gotoxy(100, 23);
		printf("   효과음 : 4");
		gotoxy(100, 24);
		printf("     ON ");
	}
	gotoxy(100, 25);
	printf("└            ┘ ");

	// 메인 화면
	while (true)
	{
		int i = 0;
		int POS = 0;

		while (1)
		{
			if (kbhit() == 1)
			{
				ch = getch();
				if (ch == '1')
				{
					SendMsg("bgm1.wav");
					gotoxy(100, 22); printf("   BGM ON  : 3");
				}
				else if (ch == '2')
				{
					SendMsg("bgm2.wav");
					gotoxy(100, 22); printf("   BGM2 ON : 3");
				}
				else if (ch == '3')
				{
					SendMsg("no BGM");
					gotoxy(100, 22); printf("   BGM OFF : 1");
				}
				else if (ch == '4')
				{
					sfx_on = sfx_on ? 0 : 1; // 1 0 toggle
					if (sfx_on == 1)
					{
						gotoxy(100, 23);
						printf("   효과음 : 4");
						gotoxy(100, 24);
						printf("     ON ");
					}
					else
					{
						gotoxy(100, 23);
						printf("   효과음 : 4");
						gotoxy(100, 24);
						printf("     OFF");
					}
				}
				if (ch == UP)
				{
					if (POS == 0) POS = 2;
					else POS -= 1;
				}
				else if (ch == DOWN)
				{
					if (POS == 2) POS = 0;
					else POS += 1;
				}
				else if (ch == 13) //엔터를 눌렀을 때
					break;
			}
			switch (POS)
			{
			case 0:
				// 1. play를 선택했을 때 play 앞에 세모가 깜빡거림
				if (i)
				{
					int c1 = rand() % 16;
					textcolor(c1, WHITE);
					gotoxy(30, 3); printf("■■■   ■■■   ■■■      ■■■   ■    ■ ■■   ■");
					gotoxy(30, 4); printf("■   ■|■    ■|■           ■   ■  ■    ■|■■   ■");
					gotoxy(30, 5); printf("■   ■|■    ■|■   ■■    ■■■■|■    ■|■ ■  ■");
					gotoxy(30, 6); printf("■   ■|■    ■|■    ■     ■   ■ |■    ■|■  ■ ■");
					gotoxy(30, 7); printf("■■■   ■■■    ■■■     ■   ■   ■■■  ■   ■■");
					textcolor(BLACK, WHITE);
					textcolor(MAGENTA1, WHITE);
					gotoxy(2, 2 + 1); printf("　　　　 ∩＿＿_∩\n");
					gotoxy(2, 2 + 2); printf("　　　　 | ノ　　`(つ)\n");
					gotoxy(2, 2 + 3); printf("　　　　/　●　 ●|| ｜\n");
					gotoxy(2, 2 + 4); printf("　 ／＼｜　 (_●_)ミ /\n");
					gotoxy(2, 2 + 5); printf("- ／　彡､　 |∪|ノ/\n");
					gotoxy(2, 2 + 6); printf(" (∪／＼　　  ノ ／\n");
					gotoxy(2, 2 + 7); printf("_￣　 /　　　  ／\n");
					gotoxy(2, 2 + 8); printf("＿＿ ｜　　　  /\n");
					gotoxy(2, 2 + 9); printf("＿＿ ∧　　 ￣￣)   \n");
					gotoxy(2, 2 + 10); printf("＿　/　＼＿ /　/   \n");
					gotoxy(2, 2 + 11); printf("―／　／　  (　＼  \n");
					gotoxy(2, 2 + 12); printf("-/　／　　　＼＿)  \n");
					gotoxy(2, 2 + 13); printf("｜ /               \n");
					gotoxy(2, 2 + 14); printf("(ノ                \n");

					gotoxy(90, 2 + 1); printf("　　　　 ∩＿＿_∩\n");
					gotoxy(90, 2 + 2); printf("　　　　 | ノ　　`(つ)\n");
					gotoxy(90, 2 + 3); printf("　　　　/　●　 ●|| ｜\n");
					gotoxy(90, 2 + 4); printf("　 ／＼｜　 (_●_)ミ /\n");
					gotoxy(90, 2 + 5); printf("- ／　彡､　 |∪|ノ/\n");
					gotoxy(90, 2 + 6); printf(" (∪／＼　　  ノ ／\n");
					gotoxy(90, 2 + 7); printf("_￣　 /　　　  ／\n");
					gotoxy(90, 2 + 8); printf("＿＿ ｜　　　  /\n");
					gotoxy(90, 2 + 9); printf("＿＿ ∧　　 ￣￣)   \n");
					gotoxy(90, 2 + 10); printf("＿　/　＼＿ /　/   \n");
					gotoxy(90, 2 + 11); printf("―／　／　  (　＼  \n");
					gotoxy(90, 2 + 12); printf("-/　／　　　＼＿)  \n");
					gotoxy(90, 2 + 13); printf("｜ /               \n");
					gotoxy(90, 2 + 14); printf("(ノ                \n");
					textcolor(BLACK, WHITE);
				}
				else
				{
					gotoxy(30, 3); printf("□□□   □□□   □□□      □□□   □    □ □□   □");
					gotoxy(30, 4); printf("□   □|□    □|□           □   □  □    □|□□   □");
					gotoxy(30, 5); printf("□   □|□    □|□   □□    □□□□|□    □|□ □  □");
					gotoxy(30, 6); printf("□   □|□    □|□    □     □   □ |□    □|□  □ □");
					gotoxy(30, 7); printf("□□□   □□□    □□□     □   □   □□□  □   □□");
					textcolor(MAGENTA1, WHITE);
					gotoxy(2, 2 + 9); printf("＿＿  |　　   ＼       \n");
					gotoxy(2, 2 + 10); printf("＿　  /　/ ＼　＼     \n");
					gotoxy(2, 2 + 11); printf("――(___／　 ＼ ＼    \n");
					gotoxy(2, 2 + 12); printf(" 　      　   ＼ ＼   \n");
					gotoxy(2, 2 + 13); printf("		＼＿)            \n");
					gotoxy(2, 2 + 14); printf("   \n");

					gotoxy(90, 2 + 9); printf("＿＿  |　　   ＼       \n");
					gotoxy(90, 2 + 10); printf("＿　  /　/ ＼　＼     \n");
					gotoxy(90, 2 + 11); printf("――(___／　 ＼ ＼    \n");
					gotoxy(90, 2 + 12); printf(" 　      　   ＼ ＼   \n");
					gotoxy(90, 2 + 13); printf("		＼＿)            \n");
					gotoxy(90, 2 + 14); printf("   \n");
					textcolor(BLACK, WHITE);
				}
				i = i ? 0 : 1;
				if (i)
				{
					textcolor(BLUE1, WHITE);
					gotoxy(30, 12); printf("┌──────────────────────────┐");
					gotoxy(30, 13); printf("│                  ▷  1. PLAY                       │");
					gotoxy(30, 14); printf("└──────────────────────────┘");
					textcolor(BLACK, WHITE);
				}
				else
				{
					textcolor(BLUE1, WHITE);
					gotoxy(30, 12); printf("┌──────────────────────────┐");
					gotoxy(30, 13); printf("│                  ▶  1. PLAY                       │");
					gotoxy(30, 14); printf("└──────────────────────────┘");
					textcolor(BLACK, WHITE);
				}
				gotoxy(30, 15); printf("┌──────────────────────────┐");
				gotoxy(30, 16); printf("│                  2. HOW TO PLAY                    │");
				gotoxy(30, 17); printf("└──────────────────────────┘");
				gotoxy(30, 18); printf("┌──────────────────────────┐");
				gotoxy(30, 19); printf("│                     3. EXIT                        │");
				gotoxy(30, 20); printf("└──────────────────────────┘");
				break;

			case 1:
				// 2. how to play를 선택했을 때  how to play 앞에 세모가 깜빡거림
				if (i)
				{
					int c1 = rand() % 16;
					textcolor(c1, WHITE);
					gotoxy(30, 3); printf("■■■   ■■■   ■■■      ■■■   ■    ■ ■■   ■");
					gotoxy(30, 4); printf("■   ■|■    ■|■           ■   ■  ■    ■|■■   ■");
					gotoxy(30, 5); printf("■   ■|■    ■|■   ■■    ■■■■|■    ■|■ ■  ■");
					gotoxy(30, 6); printf("■   ■|■    ■|■    ■     ■   ■ |■    ■|■  ■ ■");
					gotoxy(30, 7); printf("■■■   ■■■    ■■■     ■   ■   ■■■  ■   ■■");
					textcolor(BLACK, WHITE);
					textcolor(MAGENTA1, WHITE);
					gotoxy(2, 2 + 1); printf("　　　　 ∩＿＿_∩\n");
					gotoxy(2, 2 + 2); printf("　　　　 | ノ　　`(つ)\n");
					gotoxy(2, 2 + 3); printf("　　　　/　●　 ●|| ｜\n");
					gotoxy(2, 2 + 4); printf("　 ／＼｜　 (_●_)ミ /\n");
					gotoxy(2, 2 + 5); printf("- ／　彡､　 |∪|ノ/\n");
					gotoxy(2, 2 + 6); printf(" (∪／＼　　  ノ ／\n");
					gotoxy(2, 2 + 7); printf("_￣　 /　　　  ／\n");
					gotoxy(2, 2 + 8); printf("＿＿ ｜　　　  /\n");
					gotoxy(2, 2 + 9); printf("＿＿ ∧　　 ￣￣)   \n");
					gotoxy(2, 2 + 10); printf("＿　/　＼＿ /　/   \n");
					gotoxy(2, 2 + 11); printf("―／　／　  (　＼  \n");
					gotoxy(2, 2 + 12); printf("-/　／　　　＼＿)  \n");
					gotoxy(2, 2 + 13); printf("｜ /               \n");
					gotoxy(2, 2 + 14); printf("(ノ                \n");

					gotoxy(90, 2 + 1); printf("　　　　 ∩＿＿_∩\n");
					gotoxy(90, 2 + 2); printf("　　　　 | ノ　　`(つ)\n");
					gotoxy(90, 2 + 3); printf("　　　　/　●　 ●|| ｜\n");
					gotoxy(90, 2 + 4); printf("　 ／＼｜　 (_●_)ミ /\n");
					gotoxy(90, 2 + 5); printf("- ／　彡､　 |∪|ノ/\n");
					gotoxy(90, 2 + 6); printf(" (∪／＼　　  ノ ／\n");
					gotoxy(90, 2 + 7); printf("_￣　 /　　　  ／\n");
					gotoxy(90, 2 + 8); printf("＿＿ ｜　　　  /\n");
					gotoxy(90, 2 + 9); printf("＿＿ ∧　　 ￣￣)   \n");
					gotoxy(90, 2 + 10); printf("＿　/　＼＿ /　/   \n");
					gotoxy(90, 2 + 11); printf("―／　／　  (　＼  \n");
					gotoxy(90, 2 + 12); printf("-/　／　　　＼＿)  \n");
					gotoxy(90, 2 + 13); printf("｜ /               \n");
					gotoxy(90, 2 + 14); printf("(ノ                \n");
					textcolor(BLACK, WHITE);
				}
				else
				{
					gotoxy(30, 3); printf("□□□   □□□   □□□      □□□   □    □ □□   □");
					gotoxy(30, 4); printf("□   □|□    □|□           □   □  □    □|□□   □");
					gotoxy(30, 5); printf("□   □|□    □|□   □□    □□□□|□    □|□ □  □");
					gotoxy(30, 6); printf("□   □|□    □|□    □     □   □ |□    □|□  □ □");
					gotoxy(30, 7); printf("□□□   □□□    □□□     □   □   □□□  □   □□");
					textcolor(MAGENTA1, WHITE);
					gotoxy(2, 2 + 9); printf("＿＿  |　　   ＼       \n");
					gotoxy(2, 2 + 10); printf("＿　  /　/ ＼　＼     \n");
					gotoxy(2, 2 + 11); printf("――(___／　 ＼ ＼    \n");
					gotoxy(2, 2 + 12); printf(" 　      　   ＼ ＼   \n");
					gotoxy(2, 2 + 13); printf("		＼＿)            \n");

					gotoxy(2, 2 + 14); printf("   \n");
					gotoxy(90, 2 + 9); printf("＿＿  |　　   ＼       \n");
					gotoxy(90, 2 + 10); printf("＿　  /　/ ＼　＼     \n");
					gotoxy(90, 2 + 11); printf("――(___／　 ＼ ＼    \n");
					gotoxy(90, 2 + 12); printf(" 　      　   ＼ ＼   \n");
					gotoxy(90, 2 + 13); printf("		＼＿)            \n");
					gotoxy(90, 2 + 14); printf("   \n");
					textcolor(BLACK, WHITE);
				}
				i = i ? 0 : 1;
				gotoxy(30, 12); printf("┌──────────────────────────┐");
				gotoxy(30, 13); printf("│                     1. PLAY                        │");
				gotoxy(30, 14); printf("└──────────────────────────┘");
				if (i)
				{
					textcolor(BLUE1, WHITE);
					gotoxy(30, 15); printf("┌──────────────────────────┐");
					gotoxy(30, 16); printf("│                ▷  2. HOW TO PLAY                  │");
					gotoxy(30, 17); printf("└──────────────────────────┘");
					textcolor(BLACK, WHITE);
				}
				else
				{
					textcolor(BLUE1, WHITE);
					gotoxy(30, 15); printf("┌──────────────────────────┐");
					gotoxy(30, 16); printf("│                ▶  2. HOW TO PLAY                  │");
					gotoxy(30, 17); printf("└──────────────────────────┘");
					textcolor(BLACK, WHITE);
				}
				gotoxy(30, 18); printf("┌──────────────────────────┐");
				gotoxy(30, 19); printf("│                     3. EXIT                        │");
				gotoxy(30, 20); printf("└──────────────────────────┘");
				break;

			case 2:
				// 3. exit를 선택했을 때  exit 앞에 세모가 깜빡거림
				if (i)
				{
					int c1 = rand() % 16;
					textcolor(c1, WHITE);
					gotoxy(30, 3); printf("■■■   ■■■   ■■■      ■■■   ■    ■ ■■   ■");
					gotoxy(30, 4); printf("■   ■|■    ■|■           ■   ■  ■    ■|■■   ■");
					gotoxy(30, 5); printf("■   ■|■    ■|■   ■■    ■■■■|■    ■|■ ■  ■");
					gotoxy(30, 6); printf("■   ■|■    ■|■    ■     ■   ■ |■    ■|■  ■ ■");
					gotoxy(30, 7); printf("■■■   ■■■    ■■■     ■   ■   ■■■  ■   ■■");
					textcolor(BLACK, WHITE);
					textcolor(MAGENTA1, WHITE);
					gotoxy(2, 2 + 1); printf("　　　　 ∩＿＿_∩\n");
					gotoxy(2, 2 + 2); printf("　　　　 | ノ　　`(つ)\n");
					gotoxy(2, 2 + 3); printf("　　　　/　●　 ●|| ｜\n");
					gotoxy(2, 2 + 4); printf("　 ／＼｜　 (_●_)ミ /\n");
					gotoxy(2, 2 + 5); printf("- ／　彡､　 |∪|ノ/\n");
					gotoxy(2, 2 + 6); printf(" (∪／＼　　  ノ ／\n");
					gotoxy(2, 2 + 7); printf("_￣　 /　　　  ／\n");
					gotoxy(2, 2 + 8); printf("＿＿ ｜　　　  /\n");
					gotoxy(2, 2 + 9); printf("＿＿ ∧　　 ￣￣)   \n");
					gotoxy(2, 2 + 10); printf("＿　/　＼＿ /　/   \n");
					gotoxy(2, 2 + 11); printf("―／　／　  (　＼  \n");
					gotoxy(2, 2 + 12); printf("-/　／　　　＼＿)  \n");
					gotoxy(2, 2 + 13); printf("｜ /               \n");
					gotoxy(2, 2 + 14); printf("(ノ                \n");

					gotoxy(90, 2 + 1); printf("　　　　 ∩＿＿_∩\n");
					gotoxy(90, 2 + 2); printf("　　　　 | ノ　　`(つ)\n");
					gotoxy(90, 2 + 3); printf("　　　　/　●　 ●|| ｜\n");
					gotoxy(90, 2 + 4); printf("　 ／＼｜　 (_●_)ミ /\n");
					gotoxy(90, 2 + 5); printf("- ／　彡､　 |∪|ノ/\n");
					gotoxy(90, 2 + 6); printf(" (∪／＼　　  ノ ／\n");
					gotoxy(90, 2 + 7); printf("_￣　 /　　　  ／\n");
					gotoxy(90, 2 + 8); printf("＿＿ ｜　　　  /\n");
					gotoxy(90, 2 + 9); printf("＿＿ ∧　　 ￣￣)   \n");
					gotoxy(90, 2 + 10); printf("＿　/　＼＿ /　/   \n");
					gotoxy(90, 2 + 11); printf("―／　／　  (　＼  \n");
					gotoxy(90, 2 + 12); printf("-/　／　　　＼＿)  \n");
					gotoxy(90, 2 + 13); printf("｜ /               \n");
					gotoxy(90, 2 + 14); printf("(ノ                \n");
					textcolor(BLACK, WHITE);
				}
				else
				{
					gotoxy(30, 3); printf("□□□   □□□   □□□      □□□   □    □ □□   □");
					gotoxy(30, 4); printf("□   □|□    □|□           □   □  □    □|□□   □");
					gotoxy(30, 5); printf("□   □|□    □|□   □□    □□□□|□    □|□ □  □");
					gotoxy(30, 6); printf("□   □|□    □|□    □     □   □ |□    □|□  □ □");
					gotoxy(30, 7); printf("□□□   □□□    □□□     □   □   □□□  □   □□");
					textcolor(MAGENTA1, WHITE);
					gotoxy(2, 2 + 9); printf("＿＿  |　　   ＼       \n");
					gotoxy(2, 2 + 10); printf("＿　  /　/ ＼　＼     \n");
					gotoxy(2, 2 + 11); printf("――(___／　 ＼ ＼    \n");
					gotoxy(2, 2 + 12); printf(" 　      　   ＼ ＼   \n");
					gotoxy(2, 2 + 13); printf("		＼＿)            \n");

					gotoxy(2, 2 + 14); printf("   \n");
					gotoxy(90, 2 + 9); printf("＿＿  |　　   ＼       \n");
					gotoxy(90, 2 + 10); printf("＿　  /　/ ＼　＼     \n");
					gotoxy(90, 2 + 11); printf("――(___／　 ＼ ＼    \n");
					gotoxy(90, 2 + 12); printf(" 　      　   ＼ ＼   \n");
					gotoxy(90, 2 + 13); printf("		＼＿)         \n");
					gotoxy(90, 2 + 14); printf("   \n");
					textcolor(BLACK, WHITE);
				}
				i = i ? 0 : 1;
				gotoxy(30, 12); printf("┌──────────────────────────┐");
				gotoxy(30, 13); printf("│                     1. PLAY                        │");
				gotoxy(30, 14); printf("└──────────────────────────┘");
				gotoxy(30, 15); printf("┌──────────────────────────┐");
				gotoxy(30, 16); printf("│                  2. HOW TO PLAY                    │");
				gotoxy(30, 17); printf("└──────────────────────────┘");
				if (i)
				{
					textcolor(BLUE1, WHITE);
					gotoxy(30, 18); printf("┌──────────────────────────┐");
					gotoxy(30, 19); printf("│                  ▷  3. EXIT                       │");
					gotoxy(30, 20); printf("└──────────────────────────┘");
					textcolor(BLACK, WHITE);
				}
				else
				{
					textcolor(BLUE1, WHITE);
					gotoxy(30, 18); printf("┌──────────────────────────┐");
					gotoxy(30, 19); printf("│                  ▶  3. EXIT                       │");
					gotoxy(30, 20); printf("└──────────────────────────┘");
					textcolor(BLACK, WHITE);
				}
				break;

			default: break;

			}
			Sleep(200);
		}

		cls(WHITE, BLACK);
		// play를 선택하고 엔터를 누른 경우 
		if (POS == 0)
		{ // 게임 대기화면
			draw_box(15, 2, 55, 8, '□');
			textcolor(BLUE1, WHITE);
			gotoxy(19, 8);
			printf("|  /");
			gotoxy(19, 9);
			printf("| /");
			gotoxy(19, 10);
			printf("|/");
			textcolor(BLACK, WHITE);
			gotoxy(19, 5);
			printf("아무키나 누르면 게임을 시작됩니다.");
			putdog(0, HEIGHT - 14);
			draw_box4(40, 0, 81, 25, '□');
			infoDraw2();
			draw_box2(0, 1, 79, 24, '□');

			while (1) {
				// 아무키나 입력을 받으면 게임 시작
				if (getch())
					break;
			}
			//게임 화면으로 넘어감
			break;
		}
		// how to play를 선택하고 엔터를 누른 경우 
		else if (POS == 1)
		{
			printf("how to play를 눌렀습니다.");
			// 게임 설명 화면이 나오고 아무키나 입력을 받을 경우 메인화면으로 돌아옴
			infoDraw();
			goto START;
		}
		// exit를 선택하고 엔터를 누른 경우 
		else if (POS == 2)
		{
			endDraw();
		}
		// 게임 종료
		exit(0);
	}

	newx = oldx = 0;
	newy = oldy = HEIGHT - 14;

PLAY:

	cls(WHITE, BLACK);
	init_game();
	removeCursor();
	textcolor(BLACK, WHITE);

	int dog_y = newy + 14;
	double life = 4;
	int score = 0;
	clock_t start, current;	//점수 변수 초기화
	start = clock();		//시작시간 초기화
	int p1_frame_sync = 5;

	erase_block();
	init_block();
	infoDraw2();
	init_heart();
	init_jelly();
	show_block();
	putdog(oldx, oldy);
	ch = DOWN; // 초기값 정지상태
	keep_moving = 1;
	draw_box2(0, 1, 80, 24, '□'); // 화면에 box를 그린다.
	draw_box3(40, 0, 80, 1, '□');
	draw_box4(40, 0, 81, 25, '□');

	while (1) {

		if (crash1(block_x, oldy, life))
		{
			// 부딪혔을 때 효과음 
			if (sfx_on) {
				PlaySound(TEXT("crash.wav"), 0, SND_FILENAME | SND_ASYNC);
			}
			//충돌시 life 1씩 감소  
			life--;
			// 블록에 부딪혔을 때 이펙트
			block_effect(block_x);
			dog_effect(oldx, oldy);
			erase_block_effect(block_x);
			// life가 0일 시 게임 종료 
			if (life == 0) break;
		}

		if (crash2(heart_x, oldy, life))
		{
			// 회복하였을 때 효과음 
			if (sfx_on) {
				PlaySound(TEXT("멍.wav"), 0, SND_FILENAME | SND_ASYNC);
			}
			//충돌시 life 1 감소 (속도를 block의 반으로 줄였기 때문에 -0.5)
			if (life < 4)
				life += 0.5;
			// 하트를 먹었을 때 이펙트 
			heart_effect(heart_x);
			erase_heart();
			//if (life == 0) break;
		}

		if (crash3(jelly_x, oldy, life))
		{
			// 회복하였을 때 효과음 
			if (sfx_on) {
				PlaySound(TEXT("멍.wav"), 0, SND_FILENAME | SND_ASYNC);
			}
			//충돌시 life 1 감소 (속도를 block의 반으로 줄였기 때문에 -0.5)
			score += 5;
			putdog(oldx, oldy);
			// 젤리를 먹었을 때 이펙트 
			jelly_effect(jelly_x);
			erase_jelly();
			//if (life == 0) break;
		}

		current = clock();			//현재시간 받아오기
		if (((current - start) / CLOCKS_PER_SEC) >= 1)
		{
			score += 5;	//스코어 UP
			start = clock();	//시작시간 초기화
		}

		// 점수를 항상 출력하면서, 1초가 지났을때 추가
		gotoxy(58, 0);
		textcolor(BLUE1, YELLOW2);
		printf("Score : %d ", score);	//점수 출력해줌.
		textcolor(BLACK, WHITE);

		if (kbhit() == 1)
		{  // 키보드가 눌려져 있으면
			ch = getch(); // key 값을 읽는다
			//
			// ESC 누르면 곧바로 게임 종료 
			if (ch == ESC)
			{
				endMessage();
				while (1)
				{
					if (kbhit() == 1)
					{
						unsigned char ch;
						ch = getch();
						// y을 누르면 게임 종료
						if (ch == 'y')
							break;
						// n를 누르면  regame
						else if (ch == 'n')
							goto PLAY;
					}
				}
				break;
			}

			if (ch == SPECIAL1 || ch == SPECIAL2)
			{ // 만약 특수키
				// 예를 들어 UP key의 경우 0xe0 0x48 두개의 문자가 들어온다.
				ch = getch();
				switch (ch)
				{
				case UP:
					if (sfx_on) 
					{
						PlaySound(TEXT("점프19.wav"), 0, SND_FILENAME | SND_ASYNC);
					}
					keep_moving = 1;
				case DOWN:
					//case LEFT:
					//case RIGHT:
					erasedog(oldx, oldy); 
					putslidingdog(oldx, oldy);

					keep_moving = 1;
					break;
					//default: // 방향키가 아니면 멈춘다
						//keep_moving = 0;
				}
			}
			else
			{
				// 특수 문자가 아니지만 AWSD를 방향키 대신 사용하는 경우 처리
			}
		}

		if (keep_moving && cnt % 2 == 0)
		{ // 움직이고 있으면
			//
			// 벽을 만나면 방향을 변경하기 추가
			// 벽을 만날때 Delay 를 감소시키면 속도가 빨라진다.
			//			
			switch (ch)
			{
			case UP:

				if (oldy > (dog_y - 22))
				{
					newy = oldy - 1;
					p1_frame_sync++;
				}
				else {
					newy = dog_y - 22;
					ch = DOWN;
				}
				break;

			case DOWN:
				if (oldy < dog_y - 14) {
					newy = oldy + 1;
					p1_frame_sync--;
				}
				else
					keep_moving = 1;
				break;
				/*case LEFT:
					if (oldx > 0 )
						newx = oldx - 1;
					break;
				case RIGHT:
					if (oldx < WIDTH - 1)
						newx = oldx + 1;
					break;*/
			}

			erasedog(oldx, oldy); // 마지막 위치의 * 를 지우고
			putdog(newx, newy); // 새로운 위치에서 * 를 표시한다.
			oldx = newx; // 마지막 위치를 기억한다.
			oldy = newy;
			keep_moving = 1; //1:계속이동, 0:한번에 한칸씩이동
		}

		move_block(-1, 0); // x 좌표를 -1씩 , --> 왼쪽으로 이동
		if (cnt % 2 == 0)
		{
			move_heart(-1, 0);
			move_jelly(-1, 0);
		}

		Sleep(Delay); // Delay를 줄이면 속도가 빨라진다.
		cnt++;

		// 점수가 증가할수록 게임 속도 증가
		if (score > 29 && score < 31)
			Delay = 40;
		else if (score > 49 && score < 51)
			Delay = 30;
		else if (score > 69 && score < 71)
			Delay = 20;
		else if (score > 99 && score < 101)
			Delay = 10;
		else if (score > 150)
			Delay = 1;
	}

	// 게임 오버시 효과음
	if (sfx_on) 
	{
		PlaySound(TEXT("gameover.wav"), 0, SND_FILENAME | SND_ASYNC);
	}
	// 게임 오버
	gameover(score);

	// 키 입력 r, m, q
	while (1)
	{
		if (kbhit() == 1)
		{
			unsigned char ch;
			ch = getch();
			// r을 누르면 regame
			if (ch == 'r')
				goto PLAY;
			// m을 누르면 메인 화면으로
			else if (ch == 'm')
				goto START;
			// q를 누르면 게임 종료
			else if (ch == 'q')
				endDraw();
			//break;
			exit(0);
		}
	}
}