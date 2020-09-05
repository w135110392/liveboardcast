#include<stdio.h>
#include<graphics.h>
#include<conio.h>

/*
	1.初始化！
		数据


*/
IMAGE image;    //定义一张图片
IMAGE img[42];  //定义42张小图片
int map[7][6]; 
//1.初始化！
void gameInit() {
	//加载图片
	loadimage(&image, L"1111.jpg", 600, 700);
	SetWorkingImage(&image);//设置当前的工作对象
	//切割图片  100  600*700 42张
	for (int i = 0; i < 7;i++) {
	
		for (int j = 0; j < 6;j++) {
		
			getimage(&img[i*6+j], j * 100, i * 100, 100, 100);
		}
	}
	
	SetWorkingImage(NULL);
	//最后一张做成空白
	loadimage(&img[41], L"123.jpg ", 100, 100);
	
	//初始化数组
	//int n = 41;
	for (int i = 0; i < 7;i++) {
		for (int j = 0; j< 6;j++) {
			map[i][j] =i*6+j;
		}
	}
}
//绘制函数
void gamePaint() {

	//打印二维数组
	for (int i = 0; i < 7;i++) {
		for (int j = 0; j < 6;j++) {
			putimage(j * 100, i * 100, &img[map[i][j]]);
		
		}
		//printf("\n");
	}
	//putimage(0, 0, &img[41]);
}
//玩游戏
void gamePlay() {

	MOUSEMSG msg = { 0 };
	msg = GetMouseMsg();//接收鼠标消息
	int r0, c0;//空白图片的下标 标志 41这个数
	int r, c;//点击图片的下标
	int flag = 0;//标志 是否找到空白图片

	for (int i = 0; i < 7;i++) {
		for (int j = 0; j < 6;j++) {
			if (map[i][j] == 41) {//找到了
				r0 = i;
				c0 = j;
				flag = 1;
			}
		}
		if (flag) 
			break;
		
	}

	if (msg.uMsg==WM_LBUTTONDOWN) {
		//点到那张图片 就跟空白图片交换  对应的数组元素的值
		r = msg.y / 100;
		c = msg.x / 100;
		//交换
		map[r0][c0] = map[r][c];
		map[r][c] = 41;
		
		//outtextxy(0,0,L"This is a test");
	}
	

}
int main(void) {
	initgraph(600,700);
	gameInit();
	while (1) {
	
		
		gamePaint();
		gamePlay();
	}
	

	system("pause");
	/*_getch();
	closegraph();*/
	return 0;
}