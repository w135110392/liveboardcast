#include<stdio.h>
#include<graphics.h>
#include<conio.h>

/*
	1.��ʼ����
		����


*/
IMAGE image;    //����һ��ͼƬ
IMAGE img[42];  //����42��СͼƬ
int map[7][6]; 
//1.��ʼ����
void gameInit() {
	//����ͼƬ
	loadimage(&image, L"1111.jpg", 600, 700);
	SetWorkingImage(&image);//���õ�ǰ�Ĺ�������
	//�и�ͼƬ  100  600*700 42��
	for (int i = 0; i < 7;i++) {
	
		for (int j = 0; j < 6;j++) {
		
			getimage(&img[i*6+j], j * 100, i * 100, 100, 100);
		}
	}
	
	SetWorkingImage(NULL);
	//���һ�����ɿհ�
	loadimage(&img[41], L"123.jpg ", 100, 100);
	
	//��ʼ������
	//int n = 41;
	for (int i = 0; i < 7;i++) {
		for (int j = 0; j< 6;j++) {
			map[i][j] =i*6+j;
		}
	}
}
//���ƺ���
void gamePaint() {

	//��ӡ��ά����
	for (int i = 0; i < 7;i++) {
		for (int j = 0; j < 6;j++) {
			putimage(j * 100, i * 100, &img[map[i][j]]);
		
		}
		//printf("\n");
	}
	//putimage(0, 0, &img[41]);
}
//����Ϸ
void gamePlay() {

	MOUSEMSG msg = { 0 };
	msg = GetMouseMsg();//���������Ϣ
	int r0, c0;//�հ�ͼƬ���±� ��־ 41�����
	int r, c;//���ͼƬ���±�
	int flag = 0;//��־ �Ƿ��ҵ��հ�ͼƬ

	for (int i = 0; i < 7;i++) {
		for (int j = 0; j < 6;j++) {
			if (map[i][j] == 41) {//�ҵ���
				r0 = i;
				c0 = j;
				flag = 1;
			}
		}
		if (flag) 
			break;
		
	}

	if (msg.uMsg==WM_LBUTTONDOWN) {
		//�㵽����ͼƬ �͸��հ�ͼƬ����  ��Ӧ������Ԫ�ص�ֵ
		r = msg.y / 100;
		c = msg.x / 100;
		//����
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