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


//�ƶ����ַ���
void moveStr(bool flag) {
	outtextxy(200, 10, "���ڲ�������......");
	//STR str;
	//str.x = 498;
	//str.y = 10;
	//str.speed = 200;
	//
	//while (flag) {
	//	
	//	outtextxy(str.x, str.y, "���ڲ�������......");
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
//����л���ʾ����
void atPoint() {

	fillrectangle(200-1, 0, 500, 30);

}
//����
void playMusic() {
	
    PlaySound(_T("�ƻ�.wav"), NULL, SND_LOOP | SND_ASYNC);
}
//ֹͣ
void stopMusic() {

	PlaySound(NULL, NULL, SND_FILENAME);
}
void initPlay() {
	initgraph(500, 700);
	setcolor(WHITE);
	settextcolor(GREEN);
	settextstyle(20, 0, "����");
	setbkmode(TRANSPARENT);
	//���� ֹͣ�ı�������
	fillrectangle(0, 0, 500, 30);
	outtextxy(20, 10, "����");
	outtextxy(100, 10, "ֹͣ");
}
int main(void) {
	//��ʼ������
	initPlay();
	

	while (1) {
		MOUSEMSG msg = { 0 };
		msg = GetMouseMsg();
		
		if (msg.x >= 0 && msg.x < 60 && msg.y >= 0 && msg.y <= 30) {
			if (msg.uMsg == WM_LBUTTONDOWN) {
				//����
				playMusic();
				//������λ��֮ǰ����ʾ
				atPoint();
				moveStr(true);
			}

		}
		
		if (msg.x >= 100 && msg.x <= 140 && msg.y >= 0 && msg.y <= 30) {
			if (msg.uMsg == WM_LBUTTONDOWN) {
				
				//ֹͣ
				stopMusic();
				//������λ��֮ǰ����ʾ
				atPoint();
				outtextxy(200, 10, "������ֹͣ����......");
				}
		}
	}
	
	system("pause");
	closegraph();
	return 0;

}