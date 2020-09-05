#include <graphics.h>
#include <time.h>
#include<conio.h>
#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480
#define BOX_WIDTH     80
#define BOX_HEIGHT    60
#define GAME_AREA_WIDTH 448
#define BALL_NUMS 10  //球数
#define CMD_LEFT   1   //按下 ←
#define CMD_RIGHT  2   //按下 →
#define CMD_QUIT   4   //退出
#define  STEP      8   //步长
#define  RADIUS    8   //半径
#define  GAME_TIME 30  //游戏时间


void initgame();
void dispInfo();
void play();

int getKeyCommand();
int gameTime(int t);
struct Ball {
	int x;
	int y;
	int step;  //球的步长

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

	char gameRole[] = "游戏规则";
	settextcolor(GREEN);
	
	char leftDir[] = "按←键向左移动";

	char rightDir[] = "按→键向右移动";

   char introductionb[] = "倒计时为0时游戏结束.";

   char runTime[] = "游戏倒计时：";

   char receiveBallNum[] = "接到的球的数量：";

   char versionInfo[] = "版权信息：";

   char	author[] = "作者:Janny";

   char	date[] = "日期:2020年07月27日";

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

//玩游戏
void play() {
	Ball ball[BALL_NUMS];
	int i;
	int command, score = 0;
	bool bOver = false; //游戏结束
	int ownedTime = 0;//剩余时间
	for (i = 0; i < BALL_NUMS; i++) {

		ballCreate(ball,i); //球创建
}
	char strScore[10], str[15] = "你的分数:";
	char strTime[10];//时间
	int t = GetTickCount(); //操作系统启动至今经过的毫秒数

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

		//擦除游戏区域

	}
}


//创建球
void ballCreate(Ball ball[], int i) {
	ball[i].x = 16 + 45 * i;
	ball[i].y = RADIUS + rand() % 32;
	ball[i].step = 1 + rand() % 5;
}
//得分计算
void caculateScore(Ball ball[], int &score) {

	for (int i = 0; i < BALL_NUMS; i++) {

		fillcircle(ball[i].x, ball[i].y, RADIUS);
		if (ball[i].y >= WINDOW_HEIGHT + RADIUS) {

			ballCreate(ball, i);
			continue;
		}
		if (ball[i].x >= box_x + RADIUS &&

			//球x坐标≥箱子左边界+半径

			ball[i].x <= box_x + BOX_HEIGHT - RADIUS &&
			//球x坐标≤箱子右边界

			ball[i].y >= box_y - RADIUS) {

			score += 10;
			ballCreate(ball, i);
		}

	}


}
//用户按键判断
int getKeyCommand() {

	return 0;
}
//游戏计时
int gameTime(int t) {

 return  GAME_TIME-(GetTickCount() - t) / 1000;


}