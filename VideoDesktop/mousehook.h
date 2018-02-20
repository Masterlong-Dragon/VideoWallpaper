#ifndef MOUSEHOOK_H
#define MOUSEHOOK_H
#include "finddesktop.h"
#include <QDebug>
/*说明：为什么要用钩子？
窗口被强行至于底部是得不到焦点的。
为了响应用户的消息，只能用钩子的方式，获取鼠标消息，然后给窗口
*/
class MouseHook//制作一个低级系统鼠标钩子
{
public:
    MouseHook();
    void SetHook();//设置钩子
    void UnHook();//卸载钩子
    void SetWnd(HWND h);//设置消息发送对象
};

#endif // MOUSEHOOK_H
