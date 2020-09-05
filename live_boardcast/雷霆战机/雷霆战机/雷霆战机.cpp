#include <stdio.h>
#include <stdlib.h>  //动态内存分配
#include <windows.h>
#include <graphics.h>   //图形界面
#include <conio.h>
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")

DWORD t1, t2;
DWORD tt1, tt2;

//定义子弹的结构体   
typedef struct Node
{
	int x;     //数据域 用来存放子弹的坐标
	int y;

	struct Node* pnext;  //指针域 用来存放下一个子弹的内存地址
}NODE;  //没有内存  类型

NODE* pZidan = NULL;  //子弹
NODE* pMine = NULL;   //自己的飞机
NODE* pDiji = NULL;   //敌机

//创建链表
void CreateList()
{
	//创建子弹的链表
	pZidan = (NODE*)malloc(sizeof(NODE));
	pZidan->pnext = NULL;

	//创建自己的飞机
	pMine = (NODE*)malloc(sizeof(NODE));
	pMine->pnext = NULL;
	pMine->x = 320;
	pMine->y = 450;

	//创建敌机
	pDiji = (NODE*)malloc(sizeof(NODE));
	pDiji->pnext = NULL;

	t1 = GetTickCount();
	tt1 = GetTickCount();
}

//增加节点  头插法
void AddNode(int flag)  //int flag 标志
{
	//1 开辟内存
	NODE* pnew = (NODE*)malloc(sizeof(NODE));

	if (flag == 0)   //子弹
	{
		//2 填充数据
		pnew->x = pMine->x + 21;   //第一个子弹  屏幕的50  400的这个位置
		pnew->y = pMine->y - 10;

		//3 把新的节点连接到我的链表中
		pnew->pnext = pZidan->pnext;
		pZidan->pnext = pnew;
	}
	else            //敌机
	{
		//2 填充数据
		pnew->x = rand() % 640;
		pnew->y = 0;

		//3 把新的节点连接到我的链表中
		pnew->pnext = pDiji->pnext;
		pDiji->pnext = pnew;
	}
}

//判断击中
void Shoot()
{
	//敌机的两个临时指针
	NODE* pdr = pDiji->pnext;
	NODE* pdrpre = pDiji;

	//子弹的两个临时指针
	NODE* pzd = pZidan->pnext;
	NODE* pzdpre = pZidan;

	while (pdr != NULL)  //先来遍历敌机
	{
		pzd = pZidan->pnext;
		pzdpre = pZidan;

		while (pzd != NULL)
		{
			//判断子弹和敌机的坐标
			if (pzd->x >= pdr->x - 10 && pzd->x <= pdr->x + 50 &&
				pzd->y >= pdr->y - 15 && pzd->y <= pdr->y + 15)
			{
				pzdpre->pnext = pzd->pnext;
				free(pzd);

				pdrpre->pnext = pdr->pnext;
				free(pdr);

				pdr = pDiji->pnext;
				pdrpre = pDiji;
				break;
			}
			else
			{
				pzd = pzd->pnext;
				pzdpre = pzdpre->pnext;
			}
		}
		pdr = pdr->pnext;
		pdrpre = pdrpre->pnext;

	}
}

int tmain()
{
	initgraph(640, 480);   //做一个640  480的窗口
	PlaySound("The Mass.wav", NULL, SND_LOOP | SND_FILENAME | SND_ASYNC);

	char key;   //按键的输入

	CreateList();

	while (1)
	{
		BeginBatchDraw();
		cleardevice();
		//显示自己的飞机 宽50  高30 
		roundrect(pMine->x, pMine->y, pMine->x + 50, pMine->y + 30, 50, 20);

		//添加子弹
		t2 = GetTickCount();   //  t1   t2  t2-t1  
		if (t2 - t1 >= 200)
		{
			AddNode(0);   //子弹
			t1 = t2;
		}
		//显示子弹
		NODE* P = pZidan->pnext;
		while (P != NULL)
		{
			//printf  宽为10  高为15的椭圆
			//printf("%d  %d\n", P->x, P->y);
			roundrect(P->x, P->y, P->x + 10, P->y + 15, 10, 5);
			P->y--;
			P = P->pnext;
		}

		//添加敌机
		tt2 = GetTickCount();   //  t1   t2  t2-t1  
		if (tt2 - tt1 >= 1000)
		{
			AddNode(1);   //敌机
			tt1 = tt2;
		}
		//显示敌机
		P = pDiji->pnext;
		while (P != NULL)
		{
			roundrect(P->x, P->y, P->x + 30, P->y + 15, 10, 5);
			P->y++;
			P = P->pnext;
		}

		Shoot();
		Sleep(5);
		EndBatchDraw();

		//判断是否有按键
		if (kbhit())  //kbhit()  判断是否有按键  有返回1   否则返回0
		{
			//在有按键的情况下 需要执行下面面的代码
			key = getch();  //key获取按键的内容
			//上下左右  WASD  上下左右
			switch (key)
			{
			case 72:  //上
				pMine->y -= 10;
				break;
			case 80:  //下
				pMine->y += 10;
				break;
			case 75:  //左
				pMine->x -= 10;
				break;
			case 77:  //右
				pMine->x += 10;
				break;
			}
		}
	}
	return 0;
}
