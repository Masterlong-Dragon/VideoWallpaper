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
