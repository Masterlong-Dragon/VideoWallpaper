#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "videowindow.h"
#include "gifwindow.h"
#include "finddesktop.h"
#include <QCloseEvent>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    HWND desktopWnd;//桌面句柄
private slots:
    void on_Play_clicked();//播放槽

    void on_FileOpen_clicked();//文件槽

    void on_checkBox_stateChanged(int arg1);
private:
    Ui::MainWindow *ui;
    VideoWindow v;//声明一个videowindow
    GifWindow g;//声明一个gifwindow
    void closeEvent(QCloseEvent *event);//重写关闭事件
};

#endif // MAINWINDOW_H
