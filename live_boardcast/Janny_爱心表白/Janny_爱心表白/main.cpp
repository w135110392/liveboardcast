#include <stdio.h>
#include <Windows.h>
#include "love.h"
#include <conio.h>

//��Ŀָ����ʦJanny QQ:2867339945(��Ŀ��������ɼ���ʦQQ��ѯ~)

//������Ч��
void load();

//���ñ�����ǰ��ɫ
void setColor(unsigned short forewardColor, unsigned short backgroundColor);

//��ӡһ��****
void outputRepeat(const char* text);

//��ӡ����ѡ���ı�
void outputText();

int main()
{
	load();

	int choose;				//�û���ѡ��
	const char* text = "*";	//����

	do {
		system("color 0e");	//��ɫ�������׻�ɫǰ��ɫ

		//��ӡ2��***********
		outputRepeat(text);
		printf("\n");
		outputRepeat(text);

		//��ӡ����ѡ���ı�
		outputText();

		//��ӡ2��***********
		outputRepeat(text);
		printf("\n");
		outputRepeat(text);

		//�û�ѡ��İ���
		scanf_s("%d", &choose);
		system("cls");

		//�˳�
		if (choose == 5) {
			return 0;
		}

		//��ӡ����
		setColor(4, 0);
		printLove(choose);

		printf("\n�밴������ص���һ��\n");
		_getch();
		system("cls");

	} while (1);

	return 0;
}

void load()
{
	setColor(0, 14);//��ɫ�֣��׻�ɫ����

	for (int i = 0; i <= 50; i++)
	{
		printf(" ");
		printf("%d%%", i * 2);
		Sleep(101 - i);
		printf("\b\b\b");//"\b"�����λ������һλ
	}

	setColor(15, 0);//��ɫ�֣���ɫ����
	printf("\n������ɣ�");
	Sleep(2000);
	system("cls");
}

/*
���ñ���ɫ��ǰ��ɫ
	SetConsoleTextAttribute����ɫ���ã�ǰ��ɫ������ɫ����
	һ���ֽڵĵ���������ǰ��ɫ������λ�����Ʊ���ɫ��
	ǰ��ɫ��4��		2��		1��
	����ɫ��64��	32��	16��
	(0~f)�Ӻ�ɫ����ɫ
*/
void setColor(unsigned short forwardColor, unsigned short backgroundColor)
{
	//��ȡ����豸�ľ��
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);

	//һ���ֽ���������ɫ������λǰ��ɫ������λ����ɫ��
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
	printf("\n\t\t\t����Ҫ����������:\n");
	printf("\n\t\t\t1:��love��ɵ����Σ�\n");
	printf("\n\t\t\t2:������ַ���ɵ����Σ�\n");
	printf("\n\t\t\t3:�����������ɵ����Σ�\n");
	printf("\n\t\t\t4:�������ɫ��ɵ����Σ�\n");
	printf("\n\t\t\t5:�˳���\n");
}