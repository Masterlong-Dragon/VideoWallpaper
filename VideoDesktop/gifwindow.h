#ifndef GIFWINDOW_H
#define GIFWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QMovie>
#include <QMediaPlaylist>

namespace Ui {
class GifWindow;
}

class GifWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GifWindow(QWidget *parent = 0);
    ~GifWindow();
    void StartPlay(QString path);//开始
    void StopPlay();//结束
    int PlayerState;//播放状态
    QMovie *movie;//movie
    QString filePath;
private:
    Ui::GifWindow *ui;
private slots:
    void ResetGif(int currentFrame);
};

#endif // GIFWINDOW_H
