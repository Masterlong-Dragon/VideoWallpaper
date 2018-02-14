#include"finddesktop.h"

HWND findDesktopIconWnd()
{
    HWND hWorkerW = NULL;//WorkerW的句柄
    HWND hDefView = NULL;//SHELLDLL_DefView的句柄

    //找到WorkerW类的窗口
    hWorkerW = FindWindowEx(NULL, NULL, L"WorkerW", NULL);
    //通过遍历找到包含SHELLDLL_DefView的WorkerW
    while ((!hDefView) && hWorkerW)
    {
        hDefView = FindWindowEx(hWorkerW, NULL, L"SHELLDLL_DefView", NULL);
        hWorkerW = FindWindowEx(NULL, hWorkerW, L"WorkerW", NULL);
    }
    //隐藏窗口，不让mainwindow被挡住
    ShowWindow(hWorkerW,0);
    return FindWindow(L"Progman",NULL);
}
void SendMessageToDesktop()
{
     PDWORD_PTR result = NULL;
     //发送消息，召唤WorkerW
     //参考：https://www.codeproject.com/articles/856020/draw-behind-desktop-icons-in-windows
     SendMessageTimeout(FindWindow(L"Progman",NULL), 0x52c, 0, 0, SMTO_NORMAL, 1000, result);
}



