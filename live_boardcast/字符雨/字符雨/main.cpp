#include<graphics.h>
#include<stdio.h>
#include<conio.h>
#include<time.h>
#define INIT_WIDTH 640
#define INIT_HEIGHT 480
void initRain();
void downRain();
void drawRain(int n);
struct Rain
{ 
	int x;
	int y;

};
const int rainNum = 40;
Rain rains[rainNum];
int main(void) {
	srand((unsigned int)time(NULL));
	initgraph(INIT_WIDTH, INIT_HEIGHT);
	initRain();
	BeginBatchDraw();//开始批量绘图
	
	DWORD t1, t2;
	t1 = GetTickCount(); //运行到当前的时间
	while (1) {
		
		t2 = GetTickCount();
		if (t2 - t1 > 20) {
			
			cleardevice();
			downRain();
			EndBatchDraw();
			t1 = t2;
		}
	
	}

	_getch();
	closegraph();
	return 0;
}
void initRain() {

	for (int i = 0; i < rainNum;i++) {
		rains[i].x = rand()% INIT_WIDTH;
		rains[i].y = rand()% INIT_HEIGHT;
	}
}
void downRain() {
	for (int i = 0; i < rainNum;i++) {
		drawRain(i);
		rains[i].y += 5;
		if (rains[i].y > 600) {
			rains[i].x = rand() % INIT_WIDTH;
			rains[i].y = rand() % 50-70;
	 }
	}
}
void drawRain(int n) {

	for (int i = 0; i < 6;i++) {
		unsigned int greenValue = 255 - i * 40;
		settextcolor(RGB(0, greenValue, 0));
		outtextxy(rains[n].x, rains[n].y-i*20, rand()% 2+48);
	
	}
}