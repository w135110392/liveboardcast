//#include <stdio.h>
//#include <graphics.h> 
//#include <mmsystem.h>
//#pragma comment(lib,"winmm.lib")
//
//IMAGE image;	 //定义了一张图片 保存一张图片
//IMAGE img[42];   //定义42张小图片
//int   map[7][6]; //数组
//
////1.初始化！！
//void gameInit()
//{
//	mciSendString(L"open Fade.mp3", 0, 0, 0);
//	mciSendString(L"play Fade.mp3", 0, 0, 0);
//
//	//加载图片
//	loadimage(&image, L"1111.jpg", 600, 700);
//
//	//切割开来 100  600*700 简化 42
//	SetWorkingImage(&image); //设当前的工作对象 窗口
//	for (int i = 0; i < 7; i++) //i对应纵轴y
//	{
//		for (int j = 0; j < 6; j++) //j对应横轴x
//		{ //42次  
//			//一张一张保存到img数组里面
//			getimage(&img[i * 6 + j], j * 100, i * 100, 100, 100);
//			//img[] 0-41   i*6+j
//
//		}
//	}
//	SetWorkingImage(NULL); //桌面
//	//最后一张空白
//	loadimage(&img[41], L"123.jpg", 100, 100);
//
//	//初始化数组 0-41
//	for (int i = 0; i < 7; i++)
//	{
//		for (int j = 0; j < 6; j++)
//		{
//			map[i][j] = i * 6 + j;
//		}
//	}
//}
//
////绘制函数。
//void gamePaint()
//{
//	//1.
//	//打印二维数组
//	for (int i = 0; i < 7; i++)
//	{
//		for (int j = 0; j < 6; j++)
//		{
//			putimage(j * 100, i * 100, &img[map[i][j]]);
//		}
//	}
//}
//
////玩游戏。 
//void gamePlay()
//{
//	MOUSEMSG msg = { 0 };  //定义一个鼠标
//	msg = GetMouseMsg();  //接收鼠标消息
//
//	int r0, c0;		//空白图片的下标 标志 41这个数
//	int r, c;		//点击图片的下标
//	int flag = 0;   //标志 是否找到空白图片
//
//	for (int i = 0; i < 7; i++)
//	{
//		for (int j = 0; j < 6; j++)
//		{
//			if (map[i][j] == 41)  //找到了
//			{
//				r0 = i;
//				c0 = j;
//				flag = 1;
//			}
//		}
//		if (flag)
//			break;
//	}
//
//	if (msg.uMsg == WM_LBUTTONDOWN)  //鼠标左键
//	{
//		//点到哪一张  就用这张图片跟空白图片交换  对应的数组元素的值
//		r = msg.y / 100;
//		c = msg.x / 100;
//
//
//		//
//		//交换
//		map[r0][c0] = map[r][c];
//		map[r][c] = 41;
//	}
//
//}
//
//int main()
//{
//	//打开一个窗口
//	initgraph(600, 700);
//	gameInit();
//	while (1)
//	{
//		gamePaint();
//		gamePlay();
//
//	}
//
//
//	system("pause");
//	return 0;
//}