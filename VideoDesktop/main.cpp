#include "mainwindow.h"
#include <QApplication>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    SendMessageToDesktop();//发送消息
    w.desktopWnd=findDesktopIconWnd();//获取桌面句柄
    w.show();
    return a.exec();
}
