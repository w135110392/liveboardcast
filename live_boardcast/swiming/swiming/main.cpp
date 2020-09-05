#include<graphics.h>
#include<stdio.h>



#define PIC_WIDTH 800
#define PIC_HEIGHT 600
void FrameFun();

void action(int x, int y, int stronesize, int stroneweight);


IMAGE img,dest_img(PIC_WIDTH, PIC_HEIGHT);

DWORD *img_ptr1;//原图片内存指针
DWORD *img_ptr2; //处理后显示的位图内存指针
short *buff = new short[PIC_WIDTH*PIC_HEIGHT + PIC_HEIGHT];
short *buff2 = new short[PIC_WIDTH*PIC_HEIGHT + PIC_HEIGHT];

int main(void){
	initgraph(PIC_WIDTH, PIC_HEIGHT);
	SetWindowText(GetHWnd(), _T("水波纹"));
	loadimage(&img,("swiming.jpg"));
	img_ptr1 = GetImageBuffer(&img);
	img_ptr2 = GetImageBuffer(&dest_img);


	//
	memset(buff, 0, sizeof(short)*PIC_WIDTH*PIC_HEIGHT + PIC_HEIGHT);
	memset(buff2, 0, sizeof(short)*PIC_WIDTH*PIC_HEIGHT + PIC_HEIGHT);

	BeginBatchDraw();

	while(1){
		
		//电影特效
		FrameFun();
	}
	EndBatchDraw();

	system("pause");
	return 0;
}
void FrameFun() {

	
	if (MouseHit()) {
		MOUSEMSG msg = GetMouseMsg();

		if (msg.uMsg == WM_MOUSEMOVE) {
		
		
			action(msg.x,msg.y,3,200);
		
		}
		else if (msg.uMsg==WM_LBUTTONDOWN) {
		
			action(msg.x, msg.y, 5, 2000);
		}

	}
}

void action(int x, int y, int stronesize, int stroneweight) {
	int a;
	int *p = &a;
	*p = a;




}