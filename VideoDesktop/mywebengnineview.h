#ifndef MYWEBENGNINEVIEW_H
#define MYWEBENGNINEVIEW_H
#include <QWebEngineView>
#include <QWebEngineSettings>

class MyWebEngnineView:public QWebEngineView//自定义一个webview类型
{
    Q_OBJECT
public:
    explicit MyWebEngnineView(QWidget *parent = nullptr);
protected:
    QWebEngineView *createWindow(QWebEnginePage::WebWindowType);//重写这个函数，以实现超链接的跳转
};

#endif // MYWEBENGNINEVIEW_H
