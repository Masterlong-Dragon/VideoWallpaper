#ifndef WEBWINDOW_H
#define WEBWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include "mywebengnineview.h"
#include "mousehook.h"

namespace Ui {
class WebWindow;
}

class WebWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit WebWindow(QWidget *parent = 0);
    ~WebWindow();
    void StartPlay(QString path);//开始
    void StopPlay();//停止
private:
    Ui::WebWindow *ui;
    MyWebEngnineView *view;//浏览器
    MouseHook mHook;//钩子类
protected:
    bool nativeEvent(const QByteArray &eventType, void *message, long *result);//获取本地事件
};

#endif // WEBWINDOW_H
