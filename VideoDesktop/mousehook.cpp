#include "mousehook.h"
HHOOK mouseHook=NULL;//mouse hook
HWND WinId=NULL;//web窗口的句柄
HWND hWorkerW=GetWorkerW();//获取WorkerW的句柄
UINT16 codes[]={MK_LBUTTON,MK_RBUTTON,MK_MBUTTON,MK_XBUTTON1,MK_XBUTTON1};//鼠标消息的编码
LRESULT CALLBACK mouseProc(int nCode,WPARAM wParam,LPARAM lParam )//钩子回调函数

{
    if(GetForegroundWindow()==hWorkerW&&nCode==HC_ACTION)//当最前面的窗口是WorkerW（就是只有桌面）
    {
        POINT p;//定义一个坐标
        GetCursorPos(&p);//获取鼠标坐标
        ClientToScreen(WinId,&p);//转换成窗口坐标
        for (int var= 0;;var++) {
            if(wParam==WM_MOUSEMOVE){
                SendMessage(WinId,wParam,0,MAKEWPARAM(p.x,p.y));//move消息时的处理
                break;
            }
            if(wParam&codes[var]){
                SendMessage(WinId,wParam,codes[var],MAKEWPARAM(p.x,p.y));//与编码匹配上之后发送消息~
                break;
            }
        }

    }
    return CallNextHookEx(mouseHook,nCode,wParam,lParam);//下一个钩子
}

MouseHook::MouseHook()
{

}

void MouseHook::SetHook()
{
    mouseHook =SetWindowsHookEx( WH_MOUSE_LL,mouseProc,GetModuleHandle(NULL),0);//设置钩子
}

void MouseHook::UnHook()
{
    UnhookWindowsHookEx(mouseHook);//卸载钩子
}

void MouseHook::SetWnd(HWND h)
{
    WinId=h;//设置窗口句柄
}
