#include <graphics.h>
#include <stdio.h>

/**************************************************
				C����C++ѧϰ������
			С�ף���0�����IT��ҵ����н��ҵ
			   Janny��ʦ   QQ:3008661596
***************************************************/

#define PIC_HEIGHT 600	//���ڸ߶�
#define PIC_WIDTH  800	//���ڿ��

void FrameFun();	// ֡�߼�����������ÿһ֡���߼�
void RenderFun();	// ֡��Ⱦ���������ÿһ֡����ʾ�豸
void action(int x, int y, int stonesize, int stoneweight);
void nextFrame();
void RenderRipple();
float getFps();


IMAGE src_img;	// ԭλͼ		
IMAGE dest_img(PIC_WIDTH, PIC_HEIGHT);	// �������ʾ��λͼ
DWORD *img_ptr1;	//ԭͼƬ�ڴ�ָ��
DWORD *img_ptr2;	//�������ʾ��λͼ�ڴ�ָ��

//��������bufΪÿ����Ĳ�����ǰ��Ϊ��ǰ����������Ϊ��һ��ʱ�̵Ĳ���
short *buf = new short[PIC_HEIGHT * PIC_WIDTH + PIC_WIDTH];	//��ǰ����
short *buf2 = new short[PIC_HEIGHT * PIC_WIDTH + PIC_WIDTH];//��һʱ�̲���



int main()
{
	//��ʼ�豸������ͼƬ
	initgraph(PIC_WIDTH, PIC_HEIGHT);
	SetWindowText(GetHWnd(), _T("ˮ������Ч"));	//GetHWnd()��ȡͼ�δ��ڵľ��
	loadimage(&src_img, _T("swiming.jpg"));			// ����ͼƬ����ȡͼƬ���ݵ���ͼ���ڣ�����С��800*600
	setbkmode(TRANSPARENT);	//͸��ģʽ
	settextcolor(BLACK);

	settextstyle(25, 0, _T("΢���ź�"));	//�ֺţ���ȣ�����

	//��ȡ�ڴ�ָ��
	img_ptr1 = GetImageBuffer(&src_img);
	img_ptr2 = GetImageBuffer(&dest_img);

	//��ʼ����������
	memset(buf,0, (PIC_HEIGHT*PIC_WIDTH + PIC_WIDTH) * sizeof(short));
	memset(buf2,0, (PIC_HEIGHT*PIC_WIDTH + PIC_WIDTH) * sizeof(short));

	BeginBatchDraw();	//˫���壬����ʱ��Ҫ

	while (true)
	{
		FrameFun();//Ͷʯ
		RenderFun();
		FlushBatchDraw();
		Sleep(20);
	}

	EndBatchDraw();

	return 0;
}

//�߼�
void FrameFun()
{
	//���
	if (MouseHit())//��������Ϣ
	{
		MOUSEMSG msg = GetMouseMsg();//��ȡһ�������Ϣ
		//if (msg.uMsg == WM_MOUSEMOVE)
		//{
		//	action(msg.x, msg.y, 3, 256);	//�ƶ�ˮ��
		//}
		//else if (msg.uMsg == WM_LBUTTONDOWN)
		//{
		//	action(msg.x, msg.y, 5, 2560);	//���ˮ��
		//}
		if (msg.uMsg == WM_LBUTTONDOWN) {
			action(msg.x, msg.y, 5, 2560);	//���ˮ��
		}
		

		FlushMouseMsgBuffer();
	}

	//������һ֡�Ĳ���
	nextFrame();
}

//�������һ��ʱ�����е�Ĳ���
void nextFrame()
{
	for (int i = PIC_WIDTH; i < PIC_HEIGHT*(PIC_WIDTH - 1); i++)
	{
		// ��ʽ��X0'= (X1+X2+X3+X4) / 2 - X0
		buf2[i] = ((buf[i - PIC_WIDTH] + buf[i + PIC_WIDTH] + buf[i - 1] + buf[i + 1]) >> 1) - buf2[i];

		// ����˥��
		buf2[i] -= buf2[i] >> 5;
	}

	short* ptmp = buf;
	buf = buf2;
	buf2 = ptmp;
}

/**************************************
���ܣ�
	���ģ��Ͷʯͷ
����˵����
	int x, int y
			�������
	int stonesize
			��ʯͷ���Ĵ�С
	int stoneweight
			Ͷ��ʯͷ��������

// Ps: �����������һ���������Խ�����£������������ʯͷ���Ĵ�С�͡�ʯͷ��������
***************************************/
void action(int x, int y, int stonesize, int stoneweight)
{
	//ͻ�Ʊ߽粻����
	if ((x >= PIC_WIDTH - stonesize) ||	//�ұ߽�
		(x < stonesize) ||	//��߽�
		(y >= PIC_HEIGHT - stonesize) ||	//�±߽�
		(y < stonesize))	//�ϱ߽�
		return;

	for (int posx = x - stonesize; posx < x + stonesize; posx++)
	{
		for (int posy = y - stonesize; posy < y + stonesize; posy++)
		{
			if ((posx - x) * (posx - x) + (posy - y) * (posy - y) < stonesize * stonesize)
			{
				buf[PIC_WIDTH*posy + posx] += stoneweight;
			}
		}
	}
}

// ��Ⱦ
void RenderFun()
{
	RenderRipple();
	putimage(0, 0, &dest_img);

	char s[6];
	sprintf_s(s, "%.1f", getFps());
	outtextxy(0, 0, (TCHAR)s);
}

// ����ǰʱ�̲���Ӱ��֮���λͼ�������� dest_img ��
void RenderRipple()
{
	int i = 0;
	for (int y = 0; y < PIC_HEIGHT; y++)
	{
		for (int x = 0; x < PIC_WIDTH; x++)
		{
			short data = 1024 - buf[i];

			// ƫ��
			int a = ((x - PIC_WIDTH / 2) * data / 1024) + PIC_WIDTH / 2;
			int b = ((y - PIC_HEIGHT / 2) * data / 1024) + PIC_HEIGHT / 2;

			// �߽紦��
			if (a >= PIC_WIDTH)		a = PIC_WIDTH - 1;
			if (a < 0)				a = 0;
			if (b >= PIC_HEIGHT)	b = PIC_HEIGHT - 1;
			if (b < 0)				b = 0;

			// ����ƫ�� 
			img_ptr2[i] = img_ptr1[a + (b * PIC_WIDTH)];
			i++;
		}
	}
}

// ����fps
float getFps()
{
#define FPS_COUNT 8
	static int i = 0;
	static int oldTime = GetTickCount();
	static float fps;

	if (i > FPS_COUNT)
	{
		i = 0;
		int newTime = GetTickCount();
		int elapsedTime = newTime - oldTime;
		fps = FPS_COUNT / (elapsedTime / 1000.0f);
		oldTime = newTime;
	}
	i++;
	return fps;
}