#pragma once

#include <math.h>
#include <stdio.h>

extern void setColor(unsigned short ForeColor, unsigned short BackGroundColor);

void printLove(int &loveType)
{
	int s = 0;
	for (float x = 1.3; x >= -1.1; x -= 0.1)
	{
		for (float y = -2; y <= 1.4; y += 0.053)
		{
			if (pow(x*x + y * y - 1, 3) - x * x*x*y*y <= 0)
			{
				switch (loveType) {
				case 1://love
					s++;
					if (s % 4 == 1)printf("L");
					if (s % 4 == 2)printf("o");
					if (s % 4 == 3)printf("v");
					if (s % 4 == 0)printf("e");
					Sleep(2);
					break;
				case 2://随机字母
					printf("%c", rand() % 10 + rand() % 10 + 97);
					Sleep(2);
					break;
				case 3://随机数字
					printf("%d", rand() % 10);
					Sleep(2);
					break;
				case 4://随机颜色
					setColor(0, rand() % 6 + 10);
					printf(" ");
					Sleep(2);
					break;
				default:
					break;
				}
				
			}
			else {
				if (loveType == 4)	setColor(0, 0);
				printf(" ");			
			}
				
		}
		printf("\n");
	}
}