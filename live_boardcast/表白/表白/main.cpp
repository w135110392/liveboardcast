#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
void setColor(unsigned short forwordColor, unsigned backgroudColor);
void load();
void outputRepeat();
void outputText();
//进度条效果
void load() {
	setColor(0, 14);

	for (int i = 0; i <= 50; i++) {

		printf(" ");

		printf("%d%%", i*2);
		Sleep(101 - i);
		printf("\b\b\b"); //把打印的删掉 \b删掉一个 3个\b删掉3个
	}
	setColor(15, 0);
}
//设置前景，背景颜色
void setColor(unsigned short forwordColor,unsigned backgroudColor){
	//获取输出设备的句柄
	HANDLE hcon=GetStdHandle(STD_OUTPUT_HANDLE);
	//一个字节 来设置颜色 低四位前景色，高四位背景色
	SetConsoleTextAttribute(hcon, forwordColor | backgroudColor << 4);
}





int main(void) {
	load();
	outputText();



	return 0;
}
void outputRepeat() {
	const char * text = "*";


}

void outputText() {

	printf("\n\t\t\t你想要怎样的心形:\n");

	printf("\n\t\t\t1:由love组成的心形！\n");

	printf("\n\t\t\t2:由随机字符组成的心形！\n");

	printf("\n\t\t\t3:由随机数字组成的心形！\n");

	printf("\n\t\t\t4:由随机颜色组成的心形！\n");

	printf("\n\t\t\t5:退出！\n");
}