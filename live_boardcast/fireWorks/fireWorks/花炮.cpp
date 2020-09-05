#include <graphics.h>
#include <math.h>

extern const int gWidth = 1024;	// ��Ļ��
extern const int gHeight = 576;	// ��Ļ��
extern const int gNumMovers = 600;	// С������

// ����С��ṹ
extern struct Mover
{
	COLORREF	color;			// ��ɫ
	float		x, y;			// ����
	float		vX, vY;			// �ٶ�
};

extern Mover	movers[gNumMovers];			// С������;

extern int mouseVX;
extern int mouseVY;
extern int mouseX;
extern int mouseY;
extern int prevMouseX;
extern int prevMouseY;
extern bool isMouseDown;

const float gPriction = 0.9f;	// Ħ����


// ���ƶ���(һ֡)
void run()
{
	//darken();	// ȫ���䰵

	mouseVX = mouseX - prevMouseX;
	mouseVY = mouseY - prevMouseY;
	prevMouseX = mouseX;
	prevMouseY = mouseY;

	float toDist = gWidth * 0.86f;
	float stirDist = gWidth * 0.125f;//����
	float blowDist = gWidth * 0.5f;	//����

	for (int i = 0; i < gNumMovers; i++)
	{
		//��ǰ����������ٶ�
		float x = movers[i].x;
		float y = movers[i].y;
		float vX = movers[i].vX;
		float vY = movers[i].vY;

		float dX = x - mouseX;
		float dY = y - mouseY;
		float d = (float)sqrt(dX * dX + dY * dY);
		dX = d ? dX / d : 0;
		dY = d ? dY / d : 0;

		//��ըЧ��
		if (isMouseDown && d < blowDist)
		{
			float blowAcc = (1 - (d / blowDist)) * 14;
			vX += dX * blowAcc + 0.5f - float(rand()) / RAND_MAX;
			vY += dY * blowAcc + 0.5f - float(rand()) / RAND_MAX;
		}

		//�ۼ�Ч��
		if (d < toDist)
		{
			float toAcc = (1 - (d / toDist)) * gWidth * 0.0014f;
			vX -= dX * toAcc;
			vY -= dY * toAcc;
		}

		//����Ч��
		if (d < stirDist)
		{
			float mAcc = (1 - (d / stirDist)) * gWidth * 0.00026f;
			vX += mouseVX * mAcc;
			vY += mouseVY * mAcc;
		}

		//�ٶȳ���Ħ����
		vX *= gPriction;
		vY *= gPriction;

		float avgVX = (float)fabs(vX);
		float avgVY = (float)fabs(vY);
		float avgV = (avgVX + avgVY) * 0.5f;

		if (avgVX < 0.1) vX *= float(rand()) / RAND_MAX * 3;
		if (avgVY < 0.1) vY *= float(rand()) / RAND_MAX * 3;

		float sc = avgV * 0.45f;
		sc = max(min(sc, 3.5f), 0.4f);

		float nextX = x + vX;
		float nextY = y + vY;

		//�߽紦��
		if (nextX > gWidth) { nextX = gWidth;	vX *= -1; }
		else if (nextX < 0) { nextX = 0;		vX *= -1; }
		if (nextY > gHeight) { nextY = gHeight;	vY *= -1; }
		else if (nextY < 0) { nextY = 0;		vY *= -1; }

		movers[i].vX = vX;
		movers[i].vY = vY;
		movers[i].x = nextX;
		movers[i].y = nextY;

		// ��С��
		setcolor(movers[i].color);
		setfillstyle(movers[i].color);
		fillcircle(int(nextX + 0.5), int(nextY + 0.5), int(sc + 0.5));
	}
}