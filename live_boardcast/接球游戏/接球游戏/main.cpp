#include <graphics.h>
#include <time.h>
#include<conio.h>
#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480
#define BOX_WIDTH     80
#define BOX_HEIGHT    60
#define GAME_AREA_WIDTH 448
#define BALL_NUMS 10  //����
#define CMD_LEFT   1   //���� ��
#define CMD_RIGHT  2   //���� ��
#define CMD_QUIT   4   //�˳�
#define  STEP      8   //����
#define  RADIUS    8   //�뾶
#define  GAME_TIME 30  //��Ϸʱ��


void initgame();
void dispInfo();
void play();

int getKeyCommand();
int gameTime(int t);
struct Ball {
	int x;
	int y;
	int step;  //��Ĳ���

};
void caculateScore(Ball ball[], int &score);
int box_x = 10;
int box_y = 420;
void ballCreate(Ball ball[], int i);
int main(void) {
	initgame();

	return 0;
}











void initgame() {
	initgraph(WINDOW_WIDTH, WINDOW_HEIGHT);
	srand(time(NULL));
	setlinecolor(YELLOW);
	setfillcolor(YELLOW);
	dispInfo();
	BeginBatchDraw();
}
void dispInfo() {

	char gameRole[] = "��Ϸ����";
	settextcolor(GREEN);
	
	char leftDir[] = "�����������ƶ�";

	char rightDir[] = "�����������ƶ�";

   char introductionb[] = "����ʱΪ0ʱ��Ϸ����.";

   char runTime[] = "��Ϸ����ʱ��";

   char receiveBallNum[] = "�ӵ������������";

   char versionInfo[] = "��Ȩ��Ϣ��";

   char	author[] = "����:Janny";

   char	date[] = "����:2020��07��27��";

   outtextxy(450, 10, gameRole);
   outtextxy(480, 30, leftDir);
   outtextxy(480, 50, rightDir);

   outtextxy(480, 80, introductionb);

   outtextxy(450, 180, runTime);

   int lineX = GAME_AREA_WIDTH + 1;
   line(lineX, 0, lineX, WINDOW_HEIGHT);
   play();



	
	_getch();
}

//����Ϸ
void play() {
	Ball ball[BALL_NUMS];
	int i;
	int command, score = 0;
	bool bOver = false; //��Ϸ����
	int ownedTime = 0;//ʣ��ʱ��
	for (i = 0; i < BALL_NUMS; i++) {

		ballCreate(ball,i); //�򴴽�
}
	char strScore[10], str[15] = "��ķ���:";
	char strTime[10];//ʱ��
	int t = GetTickCount(); //����ϵͳ�������񾭹��ĺ�����

	while (!bOver) {
		_itoa_s(score, strScore,10);
		outtextxy(570, 250, score);
		_itoa_s(ownedTime, strTime, 10);
		outtextxy(550, 180, ownedTime);

		caculateScore(ball, score);

		fillrectangle(box_x, box_y, box_x + BOX_WIDTH, box_y + BOX_HEIGHT);

		FlushBatchDraw();
		command = getKeyCommand();
		if (command&CMD_QUIT)bOver = true;
		ownedTime = gameTime(t);
		if (!ownedTime) {

			bOver = true;
			outtextxy(550, 180, "0s");
		}
		if (command&CMD_LEFT)box_x -= STEP;
		if (command&CMD_RIGHT)box_x += STEP;

		Sleep(25);

		//������Ϸ����

	}
}


//������
void ballCreate(Ball ball[], int i) {
	ball[i].x = 16 + 45 * i;
	ball[i].y = RADIUS + rand() % 32;
	ball[i].step = 1 + rand() % 5;
}
//�÷ּ���
void caculateScore(Ball ball[], int &score) {

	for (int i = 0; i < BALL_NUMS; i++) {

		fillcircle(ball[i].x, ball[i].y, RADIUS);
		if (ball[i].y >= WINDOW_HEIGHT + RADIUS) {

			ballCreate(ball, i);
			continue;
		}
		if (ball[i].x >= box_x + RADIUS &&

			//��x�����������߽�+�뾶

			ball[i].x <= box_x + BOX_HEIGHT - RADIUS &&
			//��x����������ұ߽�

			ball[i].y >= box_y - RADIUS) {

			score += 10;
			ballCreate(ball, i);
		}

	}


}
//�û������ж�
int getKeyCommand() {

	return 0;
}
//��Ϸ��ʱ
int gameTime(int t) {

 return  GAME_TIME-(GetTickCount() - t) / 1000;


}