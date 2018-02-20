#include "videowindow.h"
#include "ui_videowindow.h"

VideoWindow::VideoWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::VideoWindow)
{
    ui->setupUi(this);
    //声明
    player=new QMediaPlayer();
    videoWidget = new QVideoWidget();
    QPalette* palette = new QPalette();
    //把窗口和widget都刷成黑色
    palette->setBrush(QPalette::Background, Qt::black);//设置黑色画刷
    videoWidget->setPalette(*palette);
    window()->setPalette(*palette);
    delete palette;//删除画刷
    setCentralWidget(videoWidget);//居中
    videoWidget->setAutoFillBackground(true);//全屏
    videoWidget->setAspectRatioMode(Qt::KeepAspectRatioByExpanding);//设置窗口自适应
    player->setVideoOutput(videoWidget);//设置输出widget
    player->setVolume(0);//默认静音
    PlayerState=QMediaPlaylist::CurrentItemInLoop;//默认循环
    connect(player,SIGNAL(durationChanged(qint64)),this,SLOT(setD(qint64)));//获取视频时长
    connect(player,SIGNAL(positionChanged(qint64)),this,SLOT(ResetVideo(qint64)));//获取播放位置
}

VideoWindow::~VideoWindow()
{
    delete ui;
}
void VideoWindow::StartPlay(QString path)
{
    player->setMedia(QUrl::fromLocalFile(path));//这个是直接播放
    player->play();//播放
}

void VideoWindow::StopPlay()
{
    if(player->state()==QMediaPlayer::PlayingState)
        player->stop();//停止播放原来的视频
}

void VideoWindow::setD(qint64 d)
{
    duration=d;
}

void VideoWindow::ResetVideo(qint64 currentInfo)
{
    if(PlayerState==QMediaPlaylist::CurrentItemInLoop)//如果循环
        if(currentInfo==duration)
        {//如果播放完了
            player->setPosition(0);//设置当前进度为0
            player->play();//重新播放
        }
}

