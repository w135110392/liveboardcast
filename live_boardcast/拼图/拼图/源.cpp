//#include <stdio.h>
//#include <graphics.h> 
//#include <mmsystem.h>
//#pragma comment(lib,"winmm.lib")
//
//IMAGE image;	 //������һ��ͼƬ ����һ��ͼƬ
//IMAGE img[42];   //����42��СͼƬ
//int   map[7][6]; //����
//
////1.��ʼ������
//void gameInit()
//{
//	mciSendString(L"open Fade.mp3", 0, 0, 0);
//	mciSendString(L"play Fade.mp3", 0, 0, 0);
//
//	//����ͼƬ
//	loadimage(&image, L"1111.jpg", 600, 700);
//
//	//�и�� 100  600*700 �� 42
//	SetWorkingImage(&image); //�赱ǰ�Ĺ������� ����
//	for (int i = 0; i < 7; i++) //i��Ӧ����y
//	{
//		for (int j = 0; j < 6; j++) //j��Ӧ����x
//		{ //42��  
//			//һ��һ�ű��浽img��������
//			getimage(&img[i * 6 + j], j * 100, i * 100, 100, 100);
//			//img[] 0-41   i*6+j
//
//		}
//	}
//	SetWorkingImage(NULL); //����
//	//���һ�ſհ�
//	loadimage(&img[41], L"123.jpg", 100, 100);
//
//	//��ʼ������ 0-41
//	for (int i = 0; i < 7; i++)
//	{
//		for (int j = 0; j < 6; j++)
//		{
//			map[i][j] = i * 6 + j;
//		}
//	}
//}
//
////���ƺ�����
//void gamePaint()
//{
//	//1.
//	//��ӡ��ά����
//	for (int i = 0; i < 7; i++)
//	{
//		for (int j = 0; j < 6; j++)
//		{
//			putimage(j * 100, i * 100, &img[map[i][j]]);
//		}
//	}
//}
//
////����Ϸ�� 
//void gamePlay()
//{
//	MOUSEMSG msg = { 0 };  //����һ�����
//	msg = GetMouseMsg();  //���������Ϣ
//
//	int r0, c0;		//�հ�ͼƬ���±� ��־ 41�����
//	int r, c;		//���ͼƬ���±�
//	int flag = 0;   //��־ �Ƿ��ҵ��հ�ͼƬ
//
//	for (int i = 0; i < 7; i++)
//	{
//		for (int j = 0; j < 6; j++)
//		{
//			if (map[i][j] == 41)  //�ҵ���
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
//	if (msg.uMsg == WM_LBUTTONDOWN)  //������
//	{
//		//�㵽��һ��  ��������ͼƬ���հ�ͼƬ����  ��Ӧ������Ԫ�ص�ֵ
//		r = msg.y / 100;
//		c = msg.x / 100;
//
//
//		//
//		//����
//		map[r0][c0] = map[r][c];
//		map[r][c] = 41;
//	}
//
//}
//
//int main()
//{
//	//��һ������
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