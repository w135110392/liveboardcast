#include<stdio.h>
#include<graphics.h>
#include<stdlib.h>
#include<time.h>
#define NUM 13
//�̻���
struct Jet {
	int x;
	int y;
	int hx;
	int hy;
	bool shoot; //״̬ �Ƿ��ڷ���״̬
	DWORD t1, t2, dt; //�̻����������ٶ�
	IMAGE img[2]; //ͼƬ������ һ��һ��
	byte n : 1; //λ��  n���� 1��λ
}Jet[NUM];

//�̻�

void init(int i) {
	//��ʼ���̻���
	Jet[i].t1 = GetTickCount();//�̻�������ʼʱ��
	Jet[i].dt = rand() % 10 + 1;//1-10ms
	Jet[i].n = 0;//��ɫͼƬ
	Jet[i].shoot = false;


	

}
//����ͼƬ 
void LoadimgT(){
	IMAGE image;
	loadimage(&image,L"shoot.jpg",200,50);
	putimage(100,100,&image);
	SetWorkingImage(&image);
	int n;
	for (int i = 0; i < NUM;i++) {
		n = rand() % 5;//0-4
		getimage(&Jet[i].img[0], n * 20, 0, 20, 50);
		getimage(&Jet[i].img[1], (n +5)* 20, 0, 20, 50);
	}
	SetWorkingImage(NULL);
}

//ѡ���̻���
void choice(DWORD &t1) {

	DWORD t2 = GetTickCount();
	if (t2-t1>100) {  //��100����
	
		//13
		int n = rand() % NUM;//���ȡһ��
		if (Jet[n].shoot==false) {
			//���û���������
			//��������Ļ���ĸ�λ��

			Jet[n].x = rand() % 1180;
			Jet[n].x = rand() % 100 + 600;
			Jet[n].hx = Jet[n].x;
			Jet[n].hy= rand()%400;
			Jet[n].shoot = true;
			putimage(Jet[n].x, Jet[n].y, &Jet[n].img[Jet[n].n], SRCINVERT);
		
		}
		t1 = t2;
	}

}

void shoot() {

	for (int i = 0; i < NUM;i++) {
	
		//�ٶ�  //�Ƿ��Ƿ���״̬
		Jet[i].t2 = GetTickCount();
		if(Jet[i].t2 - Jet[i].t1 > Jet[i].dt&&Jet[i].shoot == true) {
			putimage(Jet[i].x, Jet[i].y, &Jet[i].img[Jet[i].n], SRCINVERT);
			
			
			Jet[i].y -= 5;
			Jet[i].n++;
			
			Jet[i].t1 = Jet[i].t2;
		
		
		}
	}




}
int main(void) {
	initgraph(1200,800);
	srand((unsigned int )time(NULL));
	DWORD t1 = GetTickCount();
	/*putimage(500, 300, &Jet[5].img[0]);
	putimage(500, 300, &Jet[5].img[1]);*/
	LoadimgT();
	for (int i = 0; i < NUM;i++) {
	
		init(i);
	
	}
	while(1){
		choice(t1);
	
	}
	//ˢ�ʻ�

	//����ȥ





	settextcolor(YELLOW);
	settextstyle(64, 0, L"����");
	outtextxy(400,30,L"������Ϧ��");





	Sleep(3000);
	getchar();
	return 0;
}