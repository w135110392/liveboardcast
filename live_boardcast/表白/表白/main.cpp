#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
void setColor(unsigned short forwordColor, unsigned backgroudColor);
void load();
void outputRepeat();
void outputText();
//������Ч��
void load() {
	setColor(0, 14);

	for (int i = 0; i <= 50; i++) {

		printf(" ");

		printf("%d%%", i*2);
		Sleep(101 - i);
		printf("\b\b\b"); //�Ѵ�ӡ��ɾ�� \bɾ��һ�� 3��\bɾ��3��
	}
	setColor(15, 0);
}
//����ǰ����������ɫ
void setColor(unsigned short forwordColor,unsigned backgroudColor){
	//��ȡ����豸�ľ��
	HANDLE hcon=GetStdHandle(STD_OUTPUT_HANDLE);
	//һ���ֽ� ��������ɫ ����λǰ��ɫ������λ����ɫ
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

	printf("\n\t\t\t����Ҫ����������:\n");

	printf("\n\t\t\t1:��love��ɵ����Σ�\n");

	printf("\n\t\t\t2:������ַ���ɵ����Σ�\n");

	printf("\n\t\t\t3:�����������ɵ����Σ�\n");

	printf("\n\t\t\t4:�������ɫ��ɵ����Σ�\n");

	printf("\n\t\t\t5:�˳���\n");
}