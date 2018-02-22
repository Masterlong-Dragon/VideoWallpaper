#include "mousehook.h"
HHOOK mouseHook=NULL;//mouse hook
HWND WinId=NULL;//web窗口的句柄
HWND hWorkerW=GetWorkerW();//获取WorkerW的句柄
UINT16 buttonMsg=0;//声明
UINT16 lastMsg=0;//声明
LRESULT CALLBACK mouseProc(int nCode,WPARAM wParam,LPARAM lParam )//钩子回调函数

{
    if(GetForegroundWindow()==hWorkerW&&nCode==HC_ACTION)//当最前面的窗口是WorkerW（就是只有桌面）
    {
        POINT p;//定义一个坐标
        GetCursorPos(&p);//获取鼠标坐标
        ClientToScreen(WinId,&p);//转换成窗口坐标
        //给buttonMsg赋值
        if(wParam&MK_LBUTTON)
            buttonMsg=MK_LBUTTON;
            else if(wParam&MK_MBUTTON)
                buttonMsg=MK_MBUTTON;
                else if(wParam&MK_RBUTTON)
                    buttonMsg=MK_MBUTTON;
                    else if(lastMsg==WM_MOUSEMOVE)
                        buttonMsg=0;
        SendMessage(WinId,wParam,buttonMsg,MAKEWPARAM(p.x,p.y));
        if(wParam==lastMsg)
            lastMsg=wParam;//将二者比较，判断状态变化，用于响应拖拽消息
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
