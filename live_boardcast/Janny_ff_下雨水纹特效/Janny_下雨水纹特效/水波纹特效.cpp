#include <graphics.h>
#include <stdio.h>

/**************************************************
				C语言C++学习交流加
			小白，从0想进入IT行业，高薪就业
			   Janny老师   QQ:3008661596
***************************************************/

#define PIC_HEIGHT 600	//窗口高度
#define PIC_WIDTH  800	//窗口宽度

void FrameFun();	// 帧逻辑函数，处理每一帧的逻辑
void RenderFun();	// 帧渲染函数，输出每一帧到显示设备
void action(int x, int y, int stonesize, int stoneweight);
void nextFrame();
void RenderRipple();
float getFps();


IMAGE src_img;	// 原位图		
IMAGE dest_img(PIC_WIDTH, PIC_HEIGHT);	// 处理后显示的位图
DWORD *img_ptr1;	//原图片内存指针
DWORD *img_ptr2;	//处理后显示的位图内存指针

//以下两个buf为每个点的波幅，前者为当前波幅，后者为下一个时刻的波幅
short *buf = new short[PIC_HEIGHT * PIC_WIDTH + PIC_WIDTH];	//当前波幅
short *buf2 = new short[PIC_HEIGHT * PIC_WIDTH + PIC_WIDTH];//下一时刻波幅



int main()
{
	//初始设备，加载图片
	initgraph(PIC_WIDTH, PIC_HEIGHT);
	SetWindowText(GetHWnd(), _T("水波纹特效"));	//GetHWnd()获取图形窗口的句柄
	loadimage(&src_img, _T("swiming.jpg"));			// 加载图片（读取图片数据到绘图窗口），大小：800*600
	setbkmode(TRANSPARENT);	//透明模式
	settextcolor(BLACK);

	settextstyle(25, 0, _T("微软雅黑"));	//字号，宽度，字体

	//获取内存指针
	img_ptr1 = GetImageBuffer(&src_img);
	img_ptr2 = GetImageBuffer(&dest_img);

	//初始化波幅数组
	memset(buf,0, (PIC_HEIGHT*PIC_WIDTH + PIC_WIDTH) * sizeof(short));
	memset(buf2,0, (PIC_HEIGHT*PIC_WIDTH + PIC_WIDTH) * sizeof(short));

	BeginBatchDraw();	//双缓冲，闪屏时需要

	while (true)
	{
		FrameFun();//投石
		RenderFun();
		FlushBatchDraw();
		Sleep(20);
	}

	EndBatchDraw();

	return 0;
}

//逻辑
void FrameFun()
{
	//鼠标
	if (MouseHit())//检测鼠标消息
	{
		MOUSEMSG msg = GetMouseMsg();//获取一个鼠标消息
		//if (msg.uMsg == WM_MOUSEMOVE)
		//{
		//	action(msg.x, msg.y, 3, 256);	//移动水纹
		//}
		//else if (msg.uMsg == WM_LBUTTONDOWN)
		//{
		//	action(msg.x, msg.y, 5, 2560);	//点击水纹
		//}
		if (msg.uMsg == WM_LBUTTONDOWN) {
			action(msg.x, msg.y, 5, 2560);	//点击水纹
		}
		

		FlushMouseMsgBuffer();
	}

	//计算下一帧的波幅
	nextFrame();
}

//计算出下一个时刻所有点的波幅
void nextFrame()
{
	for (int i = PIC_WIDTH; i < PIC_HEIGHT*(PIC_WIDTH - 1); i++)
	{
		// 公式：X0'= (X1+X2+X3+X4) / 2 - X0
		buf2[i] = ((buf[i - PIC_WIDTH] + buf[i + PIC_WIDTH] + buf[i - 1] + buf[i + 1]) >> 1) - buf2[i];

		// 波能衰减
		buf2[i] -= buf2[i] >> 5;
	}

	short* ptmp = buf;
	buf = buf2;
	buf2 = ptmp;
}

/**************************************
功能：
	鼠标模拟投石头
参数说明：
	int x, int y
			鼠标坐标
	int stonesize
			“石头”的大小
	int stoneweight
			投“石头”的力度

// Ps: 如果产生错误，一般就是数组越界所致，请酌情调整“石头”的大小和“石头”的力度
***************************************/
void action(int x, int y, int stonesize, int stoneweight)
{
	//突破边界不处理
	if ((x >= PIC_WIDTH - stonesize) ||	//右边界
		(x < stonesize) ||	//左边界
		(y >= PIC_HEIGHT - stonesize) ||	//下边界
		(y < stonesize))	//上边界
		return;

	for (int posx = x - stonesize; posx < x + stonesize; posx++)
	{
		for (int posy = y - stonesize; posy < y + stonesize; posy++)
		{
			if ((posx - x) * (posx - x) + (posy - y) * (posy - y) < stonesize * stonesize)
			{
				buf[PIC_WIDTH*posy + posx] += stoneweight;
			}
		}
	}
}

// 渲染
void RenderFun()
{
	RenderRipple();
	putimage(0, 0, &dest_img);

	char s[6];
	sprintf_s(s, "%.1f", getFps());
	outtextxy(0, 0, (TCHAR)s);
}

// 处理当前时刻波幅影响之后的位图，保存在 dest_img 中
void RenderRipple()
{
	int i = 0;
	for (int y = 0; y < PIC_HEIGHT; y++)
	{
		for (int x = 0; x < PIC_WIDTH; x++)
		{
			short data = 1024 - buf[i];

			// 偏移
			int a = ((x - PIC_WIDTH / 2) * data / 1024) + PIC_WIDTH / 2;
			int b = ((y - PIC_HEIGHT / 2) * data / 1024) + PIC_HEIGHT / 2;

			// 边界处理
			if (a >= PIC_WIDTH)		a = PIC_WIDTH - 1;
			if (a < 0)				a = 0;
			if (b >= PIC_HEIGHT)	b = PIC_HEIGHT - 1;
			if (b < 0)				b = 0;

			// 处理偏移 
			img_ptr2[i] = img_ptr1[a + (b * PIC_WIDTH)];
			i++;
		}
	}
}

// 计算fps
float getFps()
{
#define FPS_COUNT 8
	static int i = 0;
	static int oldTime = GetTickCount();
	static float fps;

	if (i > FPS_COUNT)
	{
		i = 0;
		int newTime = GetTickCount();
		int elapsedTime = newTime - oldTime;
		fps = FPS_COUNT / (elapsedTime / 1000.0f);
		oldTime = newTime;
	}
	i++;
	return fps;
}