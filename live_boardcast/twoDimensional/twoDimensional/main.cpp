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
	
	//����
	
	//ͼƬ
	//����
	//����
	initgraph(800,800);
	
	setbkcolor(GREEN);
	cleardevice();
	//setcolor(WHITE); //��Ч������ʹ�� setlinecolor��settextcolor
	setorigin(400,400);//������е�������Ϊ����ԭ��
	//��ɫ
	//���úõĺ궨��
	//white black red yellow green
	//RGB(RED,GREEN,BLUE);
	//��ҵ��ɫ:ɫ�� �Աȶ� ����
	
	//ͼ��
	
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
				line(-400, -400, -200, -200);//����ȷ��һ��ֱ��
				line(400, 400, 200, 200);//����ȷ��һ��ֱ��
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
	
	


	
	
	putpixel(0,0,RED);//���һ�����ص�
	
	
	
	// sin();
	
	system("pause");
	//closegraph();
	return 0;
}