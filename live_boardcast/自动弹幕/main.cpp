#include<stdio.h>
#include<Windows.h>
#include<string>



#define FILENAME "dm.txt"
#define LINE_COUT 1024
#define TIME_SPAN 8000
bool copy2Bord(const char *data,int len) {
	Sleep(1000);
		//1.打开剪贴板
	if (OpenClipboard(NULL)) {
	
		//2.清空剪贴板
		EmptyClipboard();
		//申请一块内存
		//GlobalAlloc返回内存资源的句柄
		HGLOBAL clipBuffer=GlobalAlloc(
			GMEM_DDESHARE,//用于不同程序间交换数据用的
			len+1   //内存的大小
			);
		//把内存句柄转换成地址
		char* buff=(char*)GlobalLock(clipBuffer);
		//内存拷贝
		strcpy(buff,data);
		//解锁内存
		GlobalUnlock(clipBuffer);
		//写到剪贴板
		SetClipboardData(CF_TEXT,clipBuffer);
		//关闭剪贴板
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
		printf("文件打开%s失败！", FILENAME);
		return;
	}
	char buff[LINE_COUT];
	//参数1 读到 buff 里面去 ，参数2 最大字符数，参数3 文件指针
	 while(fgets(buff, sizeof(buff), fp)) {
		 //buff->复制到剪贴板->ctrl+V ENTER

		//buff->复制到剪贴板
		 while (!copy2Bord(buff, strlen(buff) )) { }

		 //鼠标左键单击一次
		 mouse_event(MOUSEEVENTF_LEFTDOWN |
			 MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		 keybd_event(VK_CONTROL,
			 0, //扫描码
			 0, //0表示按下 KEYEVENTF_KEYUP 弹起
			 0);
		 keybd_event('V', 0, 0, 0);
		 keybd_event('V',0, KEYEVENTF_KEYUP,  0);
		 keybd_event(VK_CONTROL,0,KEYEVENTF_KEYUP,0);
		 keybd_event(VK_RETURN,0,0,0);
		 keybd_event(VK_RETURN,0,KEYEVENTF_KEYUP,0); 


		 //清理内存
		 memset(buff, 0, sizeof(buff));

		 Sleep(TIME_SPAN);
	 }
	 fclose(fp);
}




int main(void) {
	printf("准备好了吗？");
	Sleep(5000);
	
	system("pause");
	printf("已经开始了!");
			while (1) {
				sendDM();
	}



	return 0;
}
