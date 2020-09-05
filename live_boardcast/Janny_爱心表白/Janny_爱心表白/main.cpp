#include <stdio.h>
#include <Windows.h>
#include "love.h"
#include <conio.h>

//项目指导老师Janny QQ:2867339945(项目遇到问题可加老师QQ咨询~)

//进度条效果
void load();

//设置背景、前景色
void setColor(unsigned short forewardColor, unsigned short backgroundColor);

//打印一行****
void outputRepeat(const char* text);

//打印爱心选择文本
void outputText();

int main()
{
	load();

	int choose;				//用户的选择
	const char* text = "*";	//花边

	do {
		system("color 0e");	//黑色背景，米黄色前景色

		//打印2行***********
		outputRepeat(text);
		printf("\n");
		outputRepeat(text);

		//打印爱心选择文本
		outputText();

		//打印2行***********
		outputRepeat(text);
		printf("\n");
		outputRepeat(text);

		//用户选择的爱心
		scanf_s("%d", &choose);
		system("cls");

		//退出
		if (choose == 5) {
			return 0;
		}

		//打印爱心
		setColor(4, 0);
		printLove(choose);

		printf("\n请按任意键回到上一级\n");
		_getch();
		system("cls");

	} while (1);

	return 0;
}

void load()
{
	setColor(0, 14);//黑色字，米黄色背景

	for (int i = 0; i <= 50; i++)
	{
		printf(" ");
		printf("%d%%", i * 2);
		Sleep(101 - i);
		printf("\b\b\b");//"\b"将输出位置左移一位
	}

	setColor(15, 0);//白色字，黑色背景
	printf("\n加载完成！");
	Sleep(2000);
	system("cls");
}

/*
设置背景色、前景色
	SetConsoleTextAttribute的颜色设置（前景色、背景色）：
	一个字节的低四来控制前景色，高四位来控制背景色。
	前景色：4红		2绿		1蓝
	背景色：64红	32绿	16蓝
	(0~f)从黑色到白色
*/
void setColor(unsigned short forwardColor, unsigned short backgroundColor)
{
	//获取输出设备的句柄
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);

	//一个字节来设置颜色（低四位前景色，高四位背景色）
	SetConsoleTextAttribute(hCon, forwardColor | backgroundColor << 4);
}

void outputRepeat(const char* text)
{
	for (int i = 0; i <= 56; i++)
	{
		if (i >= 20)
		{
			printf(text);
			Sleep(10);
		}
		else
		{
			printf(" ");
		}
	}
}

void outputText()
{
	printf("\n\t\t\t你想要怎样的心形:\n");
	printf("\n\t\t\t1:由love组成的心形！\n");
	printf("\n\t\t\t2:由随机字符组成的心形！\n");
	printf("\n\t\t\t3:由随机数字组成的心形！\n");
	printf("\n\t\t\t4:由随机颜色组成的心形！\n");
	printf("\n\t\t\t5:退出！\n");
}