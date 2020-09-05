#include<stdio.h>
#include<Windows.h>

#define FILE_NAME "msg.txt"
void sendLoop();
void pressKey(byte vk);
void sendMsg();
void readMsg(char *buff, int len);
void copy2Board(char *buff,int len);
void pressDoubleKey(byte vk1, byte vk2);



int main(void){
	printf("���QQ\n");
	system("pause");
	printf("6��֮��ʼ......");
	Sleep(6000);
	//�Զ�����QQ��Ϣ
	sendLoop();
	return 0;
}



void sendLoop() {
	//��ȡ��Ϣ�����ڴ�
	char buff[4096];
	readMsg(buff,sizeof(buff));

	//�ٰ��ڴ��е����ݸ��Ƶ�������
	copy2Board(buff,strlen(buff));


	while (1) {
	
		for (int i = 0; i < 5;i++) {
		
			pressKey(VK_TAB);
			Sleep(500);
		
		}
		pressKey(VK_DOWN);
		printf("��");
		pressKey(VK_RETURN);
		printf("ENTER");
		sendMsg();
	}
}
void pressKey(byte vk) {

	keybd_event(vk, 0, 0, 0);
	Sleep(100);
	keybd_event(vk, 0, KEYEVENTF_KEYUP, 0);
	Sleep(100);

}
void pressDoubleKey(byte vk1, byte vk2) {
	keybd_event(vk1, 0, 0, 0);
	Sleep(100);
	keybd_event(vk2, 0, 0, 0);
	Sleep(100);
	keybd_event(vk2, 0, KEYEVENTF_KEYUP, 0);
	Sleep(100);
	keybd_event(vk1, 0, KEYEVENTF_KEYUP, 0);
	Sleep(100);
}
void sendMsg() {
	pressDoubleKey(VK_CONTROL, 'V');
	pressKey(VK_RETURN);
	Sleep(1000);
	//�رնԻ�����
	pressKey(VK_ESCAPE);	

}
void readMsg(char *buff, int len) {
	char lineBuff[1024];
	FILE * fp;
	fp = fopen(FILE_NAME, "r");
	if (fp == NULL) {
	
		printf("���ļ�ʧ��");
		exit(1);
	}
	//while (feof(fp) != EOF) {
	//	fgets(lineBuff, len, fp);
	//}
	fgets(buff, len, fp);
	fclose(fp);
	
}

void copy2Board(char *data, int len) {
	//1�򿪼�����
	if (OpenClipboard(NULL)) {
		//2��ռ�����
		EmptyClipboard();

		//3����һ��������ڴ�
	HGLOBAL clipBuffer= GlobalAlloc(
			GMEM_DDESHARE,
			len + 1
		);
		//4��ȡ����ڴ�ĵ�ַ
	char * buff = (char*)GlobalLock(clipBuffer);
	//5����
	strcpy(buff, data);
	//6��������ڴ�
	GlobalUnlock(clipBuffer);
	//7д��������
	SetClipboardData(
		CF_TEXT,
		clipBuffer

	);
	//�رռ�����
	CloseClipboard();


	}





}