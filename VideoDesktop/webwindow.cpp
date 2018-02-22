#include "webwindow.h"
#include "ui_webwindow.h"

WebWindow::WebWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WebWindow)
{
    ui->setupUi(this);
    mHook.SetWnd((HWND)window()->winId());//设置钩子所需句柄
    view=new MyWebEngnineView(this);//声明webview
}

WebWindow::~WebWindow()
{
    view->installEventFilter(this);//加载事件过滤器
    mHook.UnHook();//卸载钩子
    view->deleteLater();
}

void WebWindow::StartPlay(QString path)
{
    view->load(QUrl(path));//加载新网页
    showFullScreen();//showtime！全屏！
    view->resize(window()->size());//设置webview大小
    mHook.SetHook();//设置钩子
}

void WebWindow::StopPlay()
{
    mHook.UnHook();//卸载钩子
    view->load(QUrl(""));//加载一个空网页
}

bool WebWindow::nativeEvent(const QByteArray &eventType, void *message, long *result)//获取本地事件
{
    MSG* msg = static_cast<MSG*>(message);
    if(msg->message==WM_MOUSELEAVE)
        return true;//这里是为了去掉本来不该存在的mouseleave消息（邪术）
    return false;
}
