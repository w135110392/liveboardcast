#include<stdio.h>
#include<Windows.h>
#include<string>



#define FILENAME "dm.txt"
#define LINE_COUT 1024
#define TIME_SPAN 8000
bool copy2Bord(const char *data,int len) {
	Sleep(1000);
		//1.�򿪼�����
	if (OpenClipboard(NULL)) {
	
		//2.��ռ�����
		EmptyClipboard();
		//����һ���ڴ�
		//GlobalAlloc�����ڴ���Դ�ľ��
		HGLOBAL clipBuffer=GlobalAlloc(
			GMEM_DDESHARE,//���ڲ�ͬ����佻�������õ�
			len+1   //�ڴ�Ĵ�С
			);
		//���ڴ���ת���ɵ�ַ
		char* buff=(char*)GlobalLock(clipBuffer);
		//�ڴ濽��
		strcpy(buff,data);
		//�����ڴ�
		GlobalUnlock(clipBuffer);
		//д��������
		SetClipboardData(CF_TEXT,clipBuffer);
		//�رռ�����
		CloseClipboard();
		return true;

	}
	else {
		return false;
	}

}
void sendDM(){
	FILE* fp;
	fp = fopen(FILENAME, "r");
	if (fp == NULL) {
		printf("�ļ���%sʧ�ܣ�", FILENAME);
		return;
	}
	char buff[LINE_COUT];
	//����1 ���� buff ����ȥ ������2 ����ַ���������3 �ļ�ָ��
	 while(fgets(buff, sizeof(buff), fp)) {
		 //buff->���Ƶ�������->ctrl+V ENTER

		//buff->���Ƶ�������
		 while (!copy2Bord(buff, strlen(buff) )) { }

		 //����������һ��
		 mouse_event(MOUSEEVENTF_LEFTDOWN |
			 MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		 keybd_event(VK_CONTROL,
			 0, //ɨ����
			 0, //0��ʾ���� KEYEVENTF_KEYUP ����
			 0);
		 keybd_event('V', 0, 0, 0);
		 keybd_event('V',0, KEYEVENTF_KEYUP,  0);
		 keybd_event(VK_CONTROL,0,KEYEVENTF_KEYUP,0);
		 keybd_event(VK_RETURN,0,0,0);
		 keybd_event(VK_RETURN,0,KEYEVENTF_KEYUP,0); 


		 //�����ڴ�
		 memset(buff, 0, sizeof(buff));

		 Sleep(TIME_SPAN);
	 }
	 fclose(fp);
}




int main(void) {
	printf("׼��������");
	Sleep(5000);
	
	system("pause");
	printf("�Ѿ���ʼ��!");
			while (1) {
				sendDM();
	}



	return 0;
}
