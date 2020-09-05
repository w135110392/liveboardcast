#include<stdio.h>
#include<graphics.h>
#include<stdlib.h>
#include<time.h>
#define NUM 13
//烟花弹
struct Jet {
	int x;
	int y;
	int hx;
	int hy;
	bool shoot; //状态 是否处于发射状态
	DWORD t1, t2, dt; //烟花弹上升的速度
	IMAGE img[2]; //图片的数组 一明一暗
	byte n : 1; //位段  n变量 1个位
}Jet[NUM];

//烟花

void init(int i) {
	//初始化烟花弹
	Jet[i].t1 = GetTickCount();//烟花弹的起始时间
	Jet[i].dt = rand() % 10 + 1;//1-10ms
	Jet[i].n = 0;//暗色图片
	Jet[i].shoot = false;


	

}
//加载图片 
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

//选择烟花弹
void choice(DWORD &t1) {

	DWORD t2 = GetTickCount();
	if (t2-t1>100) {  //隔100毫秒
	
		//13
		int n = rand() % NUM;//随机取一个
		if (Jet[n].shoot==false) {
			//设置基本的属性
			//出现在屏幕的哪个位置

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
	
		//速度  //是否是发射状态
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
	//刷鲜花

	//飞上去





	settextcolor(YELLOW);
	settextstyle(64, 0, L"黑体");
	outtextxy(400,30,L"浪漫七夕节");





	Sleep(3000);
	getchar();
	return 0;
}