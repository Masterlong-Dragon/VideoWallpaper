#include "mywebengnineview.h"

MyWebEngnineView::MyWebEngnineView(QWidget *parent): QWebEngineView(parent)
{
    QWebEngineSettings* settings = QWebEngineSettings::globalSettings();
    settings->setAttribute(QWebEngineSettings::PluginsEnabled, true);//允许加载插件（flash等）
    setContextMenuPolicy(Qt::NoContextMenu);//把webview自带的迷之菜单栏取消掉
}
QWebEngineView *MyWebEngnineView::createWindow(QWebEnginePage::WebWindowType)
{
    return this;//超链接的跳转……
}
