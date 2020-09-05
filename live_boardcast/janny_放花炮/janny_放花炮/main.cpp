#include <graphics.h>
#include <math.h>
#include <time.h>


const int gWidth = 1024;	// ��Ļ��
const int gHeight = 576;	// ��Ļ��
const int gNumMovers = 600;	// С������

int		mouseX, mouseY;			// ��ǰ�������
int		mouseVX, mouseVY;		// ����ٶ�
int		prevMouseX, prevMouseY;		// �ϴ��������
bool	isMouseDown;				// �������Ƿ���

DWORD*	pBuffer;					// �Դ�ָ��

// ����С��ṹ
struct Mover
{
	COLORREF	color;			// ��ɫ
	float		x, y;			// ����
	float		vX, vY;			// �ٶ�
};

Mover	movers[gNumMovers];			// С������

extern void run();

void init();
void darken();
void delay(DWORD ms);



// ������
void main()
{
	// ������ͼ����
	initgraph(gWidth, gHeight);
	// ��������ͼģʽ
	BeginBatchDraw();

	// ��ʼ��
	init();

	// �����Ϣ����
	MOUSEMSG m;

	while (true)
	{
		// ���������Ϣ
		while (MouseHit())
		{
			m = GetMouseMsg();

			switch (m.uMsg)
			{
			case WM_MOUSEMOVE:		mouseX = m.x;	mouseY = m.y;	break;
			case WM_LBUTTONDOWN:	isMouseDown = true;				break;
			case WM_LBUTTONUP:		isMouseDown = false;			break;
			}
		}

		darken();	// ȫ���䰵

		// ���ƶ���
		run();

		// ��ʾ����Ļ�������
		FlushBatchDraw();

		// ��ʱ 20 ����
		delay(20);
	}

	// �ر�
	EndBatchDraw();
	closegraph();
}

// ȫ���䰵 50%
void darken()
{
	for (int i = gWidth * gHeight - 1; i >= 0; i--)
		if (pBuffer[i] != 0)
			pBuffer[i] = RGB(GetRValue(pBuffer[i]) >> 1, GetGValue(pBuffer[i]) >> 1, GetBValue(pBuffer[i]) >> 1);
}


// ������ʱ
void delay(DWORD ms)
{
	static DWORD oldtime = GetTickCount();

	while (GetTickCount() - oldtime < ms)
		Sleep(1);

	oldtime = GetTickCount();
}

// ��ʼ��
void init()
{
	// ��ʼ��С������
	for (int i = 0; i < gNumMovers; i++)
	{
		movers[i].color = RGB(rand() % 256, rand() % 256, rand() % 256);
		movers[i].x = gWidth * 0.5;
		movers[i].y = gHeight * 0.5;
		movers[i].vX = float(cos(float(i))) * (rand() % 34);
		movers[i].vY = float(sin(float(i))) * (rand() % 34);
	}

	// ��ʼ��������
	mouseX = prevMouseX = gWidth / 2;
	mouseY = prevMouseY = gHeight / 2;

	// �����������
	srand((unsigned int)time(NULL));

	// ��ȡ�Դ�ָ��
	pBuffer = GetImageBuffer(NULL);
}