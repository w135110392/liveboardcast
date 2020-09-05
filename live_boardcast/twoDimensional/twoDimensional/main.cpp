#include<stdio.h>
#include<graphics.h>
#include<math.h>

struct myrectangle {
	int left;
	int top;
	int right;
	int bottom;
	int speed;
	};

int main() {
	
	//文字
	
	//图片
	//像素
	//音乐
	initgraph(800,800);
	
	setbkcolor(GREEN);
	cleardevice();
	//setcolor(WHITE); //等效于连续使用 setlinecolor和settextcolor
	setorigin(400,400);//界面的中点重新作为坐标原点
	//颜色
	//设置好的宏定义
	//white black red yellow green
	//RGB(RED,GREEN,BLUE);
	//工业颜色:色相 对比度 亮度
	
	//图形
	
	setlinestyle(PS_SOLID, 1);
	setfillcolor(BLACK);
	cleardevice();
	MOUSEMSG msg;
	myrectangle rect;
	rect.left = -10;
	rect.top = -10;
	rect.right = 10;
	rect.bottom = 10;
	rect.speed = 50;
	while (1) {
		msg = GetMouseMsg();
		while (msg.uMsg == WM_LBUTTONDOWN) {
			
			if (MouseHit()) {
				fillrectangle(rect.left, rect.top, rect.right, rect.bottom);
				rect.left += -10;
				rect.top += -10;
				rect.right += 10;
				rect.bottom+= 10;
				Sleep(rect.speed);
				cleardevice();
				setlinestyle(PS_SOLID, 2);
				setlinecolor(WHITE);
				line(-400, -400, -200, -200);//两点确定一条直线
				line(400, 400, 200, 200);//两点确定一条直线
				if (rect.left<-200&&rect.top<-200&&rect.right>200&&rect.bottom>200) {
					
					
					rect.left = -10;
					rect.top = -10;
					rect.right = 10;
					rect.bottom= 10;
					
					/*rect.left += 10;
					rect.top += 10;
					rect.right -= 10;
					rect.bottom -= 10;
					fillrectangle(rect.left, rect.top, rect.right, rect.bottom);
					cleardevice();*/
					
				}
			}

		}
	
	}
	
	


	
	
	putpixel(0,0,RED);//输出一个像素点
	
	
	
	// sin();
	
	system("pause");
	//closegraph();
	return 0;
}