#include<graphics.h>
#include<stdio.h>
#include<mmsystem.h>
#include<conio.h>
#pragma comment(lib,"winmm.lib")
#include<thread>
#include<Windows.h>

void atPoint();
void moveStr(bool flag);
void playMusic();



typedef struct {
	int x;
	int y;
	int speed;
}STR;


//移动的字符串
void moveStr(bool flag) {
	outtextxy(200, 10, "正在播放音乐......");
	//STR str;
	//str.x = 498;
	//str.y = 10;
	//str.speed = 200;
	//
	//while (flag) {
	//	
	//	outtextxy(str.x, str.y, "正在播放音乐......");
	//	Sleep(str.speed);
	//	str.x -= 3;
	//	if (str.x <= 200) {
	//		Sleep(3000);
	//		str.x = 500;
	//	}
	//	atPoint();
	//	if (!flag) {
	//		break;
	//	}
	//}
}
//清除切换显示区域
void atPoint() {

	fillrectangle(200-1, 0, 500, 30);

}
//播放
void playMusic() {
	
    PlaySound(_T("黄昏.wav"), NULL, SND_LOOP | SND_ASYNC);
}
//停止
void stopMusic() {

	PlaySound(NULL, NULL, SND_FILENAME);
}
void initPlay() {
	initgraph(500, 700);
	setcolor(WHITE);
	settextcolor(GREEN);
	settextstyle(20, 0, "宋体");
	setbkmode(TRANSPARENT);
	//播放 停止的背景区域
	fillrectangle(0, 0, 500, 30);
	outtextxy(20, 10, "播放");
	outtextxy(100, 10, "停止");
}
int main(void) {
	//初始化画面
	initPlay();
	

	while (1) {
		MOUSEMSG msg = { 0 };
		msg = GetMouseMsg();
		
		if (msg.x >= 0 && msg.x < 60 && msg.y >= 0 && msg.y <= 30) {
			if (msg.uMsg == WM_LBUTTONDOWN) {
				//播放
				playMusic();
				//清除这个位置之前的显示
				atPoint();
				moveStr(true);
			}

		}
		
		if (msg.x >= 100 && msg.x <= 140 && msg.y >= 0 && msg.y <= 30) {
			if (msg.uMsg == WM_LBUTTONDOWN) {
				
				//停止
				stopMusic();
				//清除这个位置之前的显示
				atPoint();
				outtextxy(200, 10, "音乐已停止播放......");
				}
		}
	}
	
	system("pause");
	closegraph();
	return 0;

}