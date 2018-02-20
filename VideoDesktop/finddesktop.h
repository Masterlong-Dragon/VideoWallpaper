#ifndef FINDDESKTOP_H
#define FINDDESKTOP_H
#include <qt_windows.h>
/*因为msvc编译器的缘故，要链接以下库文件*/
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"User32.lib")
#pragma comment(lib,"gdi32.lib")
/*分割*/
HWND findDesktopIconWnd();//找到桌面句柄
void SendMessageToDesktop();//召唤WorkerW
HWND GetWorkerW();//得到WorkerW
#endif // FINDDESKTOP_H
