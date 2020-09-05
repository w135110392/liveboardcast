#include <graphics.h>
#include <math.h>
#include <time.h>
#include<Windows.h>
#include<thread>

const int gWidth = 1024;	// 屏幕宽
const int gHeight = 576;	// 屏幕高
const int gNumMovers = 600;	// 小球数量

int		mouseX, mouseY;			// 当前鼠标坐标
int		mouseVX, mouseVY;		// 鼠标速度
int		prevMouseX, prevMouseY;		// 上次鼠标坐标
bool	isMouseDown;				// 鼠标左键是否按下

DWORD* pBuffer;					// 显存指针

// 定义小球结构
struct Mover
{
	COLORREF	color;			// 颜色
	float		x, y;			// 坐标
	float		vX, vY;			// 速度
};

Mover	movers[gNumMovers];			// 小球数组

extern void run();

void init();
void darken();
void delay(DWORD ms);



// 主函数
void main()
{
	thread 
	// 创建绘图窗口
	initgraph(gWidth, gHeight);
	// 启用批绘图模式
	BeginBatchDraw();

	// 初始化
	init();

	// 鼠标消息变量
	MOUSEMSG m;

	while (true)
	{
		// 处理鼠标消息
		while (MouseHit())
		{
			m = GetMouseMsg();

			switch (m.uMsg)
			{
			case WM_MOUSEMOVE:		mouseX = m.x;	mouseY = m.y;	break;
			case WM_LBUTTONDOWN:	isMouseDown = true;				break;
			case WM_LBUTTONUP:		isMouseDown = false;			break;
			}
		}

		darken();	// 全屏变暗

		// 绘制动画
		run();

		// 显示缓存的绘制内容
		FlushBatchDraw();

		// 延时 20 毫秒
		delay(20);
	}


	// 关闭
	EndBatchDraw();
	closegraph();
}

// 全屏变暗 50%
void darken()
{
	for (int i = gWidth * gHeight - 1; i >= 0; i--)
		if (pBuffer[i] != 0)
			pBuffer[i] = RGB(GetRValue(pBuffer[i]) >> 1, GetGValue(pBuffer[i]) >> 1, GetBValue(pBuffer[i]) >> 1);
}


// 绝对延时
void delay(DWORD ms)
{
	static DWORD oldtime = GetTickCount();

	while (GetTickCount() - oldtime < ms)
		Sleep(1);

	oldtime = GetTickCount();
}

// 初始化
void init()
{
	// 初始化小球数组
	for (int i = 0; i < gNumMovers; i++)
	{
		movers[i].color = RGB(rand() % 256, rand() % 256, rand() % 256);
		movers[i].x = gWidth * 0.5;
		movers[i].y = gHeight * 0.5;
		movers[i].vX = float(cos(float(i))) * (rand() % 34);
		movers[i].vY = float(sin(float(i))) * (rand() % 34);
	}

	// 初始化鼠标变量
	mouseX = prevMouseX = gWidth / 2;
	mouseY = prevMouseY = gHeight / 2;

	// 设置随机种子
	srand((unsigned int)time(NULL));

	// 获取显存指针
	pBuffer = GetImageBuffer(NULL);
}