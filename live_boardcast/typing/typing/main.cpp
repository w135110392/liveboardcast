#include<stdio.h>
#include<graphics.h>
#include<conio.h>
#include<time.h>
#include<mmsystem.h>

#define WINDOW_WIDTH  640
#define WINDOW_HEIGHT 480
#define SCORE_TEXT_X 490
#define SCORE_NUMBER_X  560
#define SCORE_Y  20
#pragma comment(lib,"winmm.lib")
int fontSize[6] = {40,70,90,110,130,150};
int gScores = 0;

void goodbye();
struct s {
	int speed;

};
int columnColor[10] = {

RGB(0X00,0X00,0XFF),
RGB(0X00,0XFF,0X00),
RGB(0XFF,0XFF,0X00),
RGB(0XFF,0X00,0X00),
RGB(0X00,0XFF,0XFF),
RGB(0Xcc,0X32,0X99),
RGB(0Xff,0X24,0X00),
RGB(0X7f,0X00,0Xff),
RGB(0Xff,0X7f,0X00),
RGB(0X4d,0X4d,0Xff),

};
void welcome();
void play();
void printScores();
void welcome() {
	setcolor(YELLOW);
	settextstyle(54,0,"宋体");
	outtextxy(160,50,"打字练习");
	setcolor(WHITE);
	settextstyle(26, 0, "隶书");
	outtextxy(200, 200, "打字练习打字练习打字练习");
	outtextxy(200, 240, "打字练习打字练习打字练习");
	outtextxy(200, 280, "打字练习打字练习打字练习打字练习");
	int c = 255;
	while (!_kbhit()) {
		setcolor(RGB(c, 0, 0));
		outtextxy(280, 400, "按任意键继续");
		c -= 8;
		if (c < 0)c = 255;
		Sleep(40);
	}
	cleardevice(); 
	
}
void play() {
	char target;
	char key;
	int x, y;
	mciSendString("open 005830.mp3 alias welcome",0,0,0);
	mciSendString("play  welcome repeat", 0, 0, 0);
	
	printScores();
	s s1;
	s1.speed = 10;
	while (true) {
		
		target =  (rand() % 26)+97;
		x = (10+rand()) % (WINDOW_WIDTH - 20);
		COLORREF color = columnColor[rand() % 10];
		int size = fontSize[rand() % 6];
		settextstyle(size, 0, "微软雅黑");
		setbkmode(OPAQUE);
		for (int y = 0; y < WINDOW_HEIGHT;y++) {
			
			setcolor(color);
			if (x > SCORE_TEXT_X && y <= SCORE_Y + 40) {
				cleardevice();
				printScores();
			}
			//cleardevice();
			outtextxy(x, y, target);//显示字符
			
			if(_kbhit()){
				key = _getch();
				//答对的情况
				if ((key == target) || (key == target + 32)) {
					mciSendString("close gotmusic", 0, 0, 0);
					mciSendString("open 222123.mp3 alias gotmusic",0,0,0);
					mciSendString("play  gotmusic", 0, 0, 0);
					gScores += 10;
					cleardevice();
					printScores();
					break;
				
				}
				else if(key==27){
					goodbye();
					closegraph();
				
				}


			

			}	
			

			if (gScores>=300&&gScores <600) {
			
				s1.speed = 4;

			}
			else if(gScores >= 600&& gScores < 900){
				s1.speed = 3;

			}
			else if (gScores >= 900) {
				s1.speed = 1;
				settextstyle(fontSize[4], 0, "微软雅黑");

			}
	
			
		
			Sleep(s1.speed);

		}
	
	}

}

void goodbye() {
	cleardevice();
	setcolor(YELLOW);
	settextstyle(48,0,"黑体");
	outtextxy(300,200,"GAME OVER");


}
void printScores() {
	setcolor(GREEN);
	settextstyle(fontSize[0], 0, "微软雅黑");
	outtextxy(SCORE_TEXT_X, SCORE_Y,"分数:");
	char buff[10];
	sprintf_s(buff,"%d", gScores);
	outtextxy(SCORE_NUMBER_X, SCORE_Y, buff);

}
int main(void) {

	initgraph(WINDOW_WIDTH, WINDOW_HEIGHT);
	srand((unsigned int)time(NULL));
	welcome();
	play();

	system("pause");
	
	return 0;
}