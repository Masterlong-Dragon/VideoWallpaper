#include "gifwindow.h"
#include "ui_gifwindow.h"

GifWindow::GifWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GifWindow)
{
    ui->setupUi(this);
    filePath="";//设置路径为空
    PlayerState=QMediaPlaylist::CurrentItemInLoop;//默认循环
    ui->gifLable->setScaledContents(true);//拉伸图片
    //把窗口刷成黑色
    QPalette* palette = new QPalette();
    palette->setBrush(QPalette::Background, Qt::black);//设置黑色画刷
    window()->setPalette(*palette);
    delete palette;//删除画刷

}

GifWindow::~GifWindow()
{
    delete ui;
}

void GifWindow::StartPlay(QString path)
{
    filePath=path;
    movie = new QMovie(filePath);//设置文件路径
    ui->gifLable->setMovie(movie);
    ui->gifLable->resize(window()->size());
    movie->start();//启动动画
    connect(movie,SIGNAL(frameChanged(int)),this,SLOT(ResetGif(int)));//是否重新播放
}

void GifWindow::StopPlay()
{
    if(filePath!="")
        movie->stop();
}

void GifWindow::ResetGif(int currentFrame)
{
    if(PlayerState==QMediaPlaylist::CurrentItemOnce)
        if(currentFrame == movie->frameCount() - 1)
            movie->setPaused(true);//不循环情况下，实现播放一次
}




