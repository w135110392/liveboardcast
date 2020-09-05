#include <stdio.h>
#include <stdlib.h>  //��̬�ڴ����
#include <windows.h>
#include <graphics.h>   //ͼ�ν���
#include <conio.h>
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")

DWORD t1, t2;
DWORD tt1, tt2;

//�����ӵ��Ľṹ��   
typedef struct Node
{
	int x;     //������ ��������ӵ�������
	int y;

	struct Node* pnext;  //ָ���� ���������һ���ӵ����ڴ��ַ
}NODE;  //û���ڴ�  ����

NODE* pZidan = NULL;  //�ӵ�
NODE* pMine = NULL;   //�Լ��ķɻ�
NODE* pDiji = NULL;   //�л�

//��������
void CreateList()
{
	//�����ӵ�������
	pZidan = (NODE*)malloc(sizeof(NODE));
	pZidan->pnext = NULL;

	//�����Լ��ķɻ�
	pMine = (NODE*)malloc(sizeof(NODE));
	pMine->pnext = NULL;
	pMine->x = 320;
	pMine->y = 450;

	//�����л�
	pDiji = (NODE*)malloc(sizeof(NODE));
	pDiji->pnext = NULL;

	t1 = GetTickCount();
	tt1 = GetTickCount();
}

//���ӽڵ�  ͷ�巨
void AddNode(int flag)  //int flag ��־
{
	//1 �����ڴ�
	NODE* pnew = (NODE*)malloc(sizeof(NODE));

	if (flag == 0)   //�ӵ�
	{
		//2 �������
		pnew->x = pMine->x + 21;   //��һ���ӵ�  ��Ļ��50  400�����λ��
		pnew->y = pMine->y - 10;

		//3 ���µĽڵ����ӵ��ҵ�������
		pnew->pnext = pZidan->pnext;
		pZidan->pnext = pnew;
	}
	else            //�л�
	{
		//2 �������
		pnew->x = rand() % 640;
		pnew->y = 0;

		//3 ���µĽڵ����ӵ��ҵ�������
		pnew->pnext = pDiji->pnext;
		pDiji->pnext = pnew;
	}
}

//�жϻ���
void Shoot()
{
	//�л���������ʱָ��
	NODE* pdr = pDiji->pnext;
	NODE* pdrpre = pDiji;

	//�ӵ���������ʱָ��
	NODE* pzd = pZidan->pnext;
	NODE* pzdpre = pZidan;

	while (pdr != NULL)  //���������л�
	{
		pzd = pZidan->pnext;
		pzdpre = pZidan;

		while (pzd != NULL)
		{
			//�ж��ӵ��͵л�������
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
	initgraph(640, 480);   //��һ��640  480�Ĵ���
	PlaySound("The Mass.wav", NULL, SND_LOOP | SND_FILENAME | SND_ASYNC);

	char key;   //����������

	CreateList();

	while (1)
	{
		BeginBatchDraw();
		cleardevice();
		//��ʾ�Լ��ķɻ� ��50  ��30 
		roundrect(pMine->x, pMine->y, pMine->x + 50, pMine->y + 30, 50, 20);

		//����ӵ�
		t2 = GetTickCount();   //  t1   t2  t2-t1  
		if (t2 - t1 >= 200)
		{
			AddNode(0);   //�ӵ�
			t1 = t2;
		}
		//��ʾ�ӵ�
		NODE* P = pZidan->pnext;
		while (P != NULL)
		{
			//printf  ��Ϊ10  ��Ϊ15����Բ
			//printf("%d  %d\n", P->x, P->y);
			roundrect(P->x, P->y, P->x + 10, P->y + 15, 10, 5);
			P->y--;
			P = P->pnext;
		}

		//��ӵл�
		tt2 = GetTickCount();   //  t1   t2  t2-t1  
		if (tt2 - tt1 >= 1000)
		{
			AddNode(1);   //�л�
			tt1 = tt2;
		}
		//��ʾ�л�
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

		//�ж��Ƿ��а���
		if (kbhit())  //kbhit()  �ж��Ƿ��а���  �з���1   ���򷵻�0
		{
			//���а���������� ��Ҫִ��������Ĵ���
			key = getch();  //key��ȡ����������
			//��������  WASD  ��������
			switch (key)
			{
			case 72:  //��
				pMine->y -= 10;
				break;
			case 80:  //��
				pMine->y += 10;
				break;
			case 75:  //��
				pMine->x -= 10;
				break;
			case 77:  //��
				pMine->x += 10;
				break;
			}
		}
	}
	return 0;
}
