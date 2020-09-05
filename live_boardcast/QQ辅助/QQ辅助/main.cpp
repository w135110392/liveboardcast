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
	printf("请打开QQ\n");
	system("pause");
	printf("6秒之后开始......");
	Sleep(6000);
	//自动发送QQ信息
	sendLoop();
	return 0;
}



void sendLoop() {
	//读取信息读到内存
	char buff[4096];
	readMsg(buff,sizeof(buff));

	//再把内存中的数据复制到剪贴板
	copy2Board(buff,strlen(buff));


	while (1) {
	
		for (int i = 0; i < 5;i++) {
		
			pressKey(VK_TAB);
			Sleep(500);
		
		}
		pressKey(VK_DOWN);
		printf("↓");
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
	//关闭对话窗口
	pressKey(VK_ESCAPE);	

}
void readMsg(char *buff, int len) {
	char lineBuff[1024];
	FILE * fp;
	fp = fopen(FILE_NAME, "r");
	if (fp == NULL) {
	
		printf("打开文件失败");
		exit(1);
	}
	//while (feof(fp) != EOF) {
	//	fgets(lineBuff, len, fp);
	//}
	fgets(buff, len, fp);
	fclose(fp);
	
}

void copy2Board(char *data, int len) {
	//1打开剪贴板
	if (OpenClipboard(NULL)) {
		//2清空剪贴板
		EmptyClipboard();

		//3申请一块特殊的内存
	HGLOBAL clipBuffer= GlobalAlloc(
			GMEM_DDESHARE,
			len + 1
		);
		//4获取这块内存的地址
	char * buff = (char*)GlobalLock(clipBuffer);
	//5拷贝
	strcpy(buff, data);
	//6解锁这块内存
	GlobalUnlock(clipBuffer);
	//7写到剪贴板
	SetClipboardData(
		CF_TEXT,
		clipBuffer

	);
	//关闭剪贴板
	CloseClipboard();


	}





}