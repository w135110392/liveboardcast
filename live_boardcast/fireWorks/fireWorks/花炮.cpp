#include <graphics.h>
#include <math.h>

extern const int gWidth = 1024;	// 屏幕宽
extern const int gHeight = 576;	// 屏幕高
extern const int gNumMovers = 600;	// 小球数量

// 定义小球结构
extern struct Mover
{
	COLORREF	color;			// 颜色
	float		x, y;			// 坐标
	float		vX, vY;			// 速度
};

extern Mover	movers[gNumMovers];			// 小球数组;

extern int mouseVX;
extern int mouseVY;
extern int mouseX;
extern int mouseY;
extern int prevMouseX;
extern int prevMouseY;
extern bool isMouseDown;

const float gPriction = 0.9f;	// 摩擦力


// 绘制动画(一帧)
void run()
{
	//darken();	// 全屏变暗

	mouseVX = mouseX - prevMouseX;
	mouseVY = mouseY - prevMouseY;
	prevMouseX = mouseX;
	prevMouseY = mouseY;

	float toDist = gWidth * 0.86f;
	float stirDist = gWidth * 0.125f;//搅动
	float blowDist = gWidth * 0.5f;	//爆发

	for (int i = 0; i < gNumMovers; i++)
	{
		//当前球的坐标与速度
		float x = movers[i].x;
		float y = movers[i].y;
		float vX = movers[i].vX;
		float vY = movers[i].vY;

		float dX = x - mouseX;
		float dY = y - mouseY;
		float d = (float)sqrt(dX * dX + dY * dY);
		dX = d ? dX / d : 0;
		dY = d ? dY / d : 0;

		//爆炸效果
		if (isMouseDown && d < blowDist)
		{
			float blowAcc = (1 - (d / blowDist)) * 14;
			vX += dX * blowAcc + 0.5f - float(rand()) / RAND_MAX;
			vY += dY * blowAcc + 0.5f - float(rand()) / RAND_MAX;
		}

		//聚集效果
		if (d < toDist)
		{
			float toAcc = (1 - (d / toDist)) * gWidth * 0.0014f;
			vX -= dX * toAcc;
			vY -= dY * toAcc;
		}

		//流体效果
		if (d < stirDist)
		{
			float mAcc = (1 - (d / stirDist)) * gWidth * 0.00026f;
			vX += mouseVX * mAcc;
			vY += mouseVY * mAcc;
		}

		//速度乘以摩擦力
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

		//边界处理
		if (nextX > gWidth) { nextX = gWidth;	vX *= -1; }
		else if (nextX < 0) { nextX = 0;		vX *= -1; }
		if (nextY > gHeight) { nextY = gHeight;	vY *= -1; }
		else if (nextY < 0) { nextY = 0;		vY *= -1; }

		movers[i].vX = vX;
		movers[i].vY = vY;
		movers[i].x = nextX;
		movers[i].y = nextY;

		// 画小球
		setcolor(movers[i].color);
		setfillstyle(movers[i].color);
		fillcircle(int(nextX + 0.5), int(nextY + 0.5), int(sc + 0.5));
	}
}