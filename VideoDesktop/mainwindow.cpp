#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->Volume,SIGNAL(valueChanged(int)),v.player,SLOT(setVolume(int)));//将滑动条与视频音量绑定
    ui->checkBox->setCheckState(Qt::Checked);//默认选中
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Play_clicked()
{
    ui->fileName->clear();
    if(desktopWnd) //设置父窗体为桌面
    {
        SetParent((HWND)v.winId(), desktopWnd);
        SetParent((HWND)g.winId(), desktopWnd);
        SetParent((HWND)w.winId(), desktopWnd);
    }
    QRegExp rx("(https?|ftp|file)://[-A-Za-z0-9+&@#/%?=~_|!:,.;]+[-A-Za-z0-9+&@#/%=~_|]");//for url
    QString filePath=ui->PathEdit->toPlainText();//get path
    ui->PathEdit->clear();//clear edit
    filePath.remove("file:///");//解决拖拽路径的问题
    v.hide();//隐藏
    g.hide();//隐藏
    w.hide();//隐藏
    v.StopPlay();//停止播放（原来的视频）
    g.StopPlay();//停止播放（原来的GIF）
    w.StopPlay();//停止播放（原来的web）
    if(filePath!=""&&filePath.contains(".mp4")||filePath.contains(".avi")||filePath.contains(".mkv"))//videos
    {
  //如果不为空
         v.setWindowFlags(Qt::FramelessWindowHint);//无边框
         v.setWindowFlags(Qt::Dialog);//提升为顶级窗口
         v.showFullScreen();//showtime！全屏！
         v.StartPlay(filePath);//将控件文本传入播放路径
         showMinimized();//最小化
         ui->fileName->setText(filePath);//更新控件文本
    }
    else
        if(filePath!=""&&filePath.contains(".gif"))//如果不为空，是gif
        {
            g.setWindowFlags(Qt::FramelessWindowHint);//无边框
            g.setWindowFlags(Qt::Dialog);//提升为顶级窗口
            g.showFullScreen();//showtime！全屏！
            g.StartPlay(filePath);//将控件文本传入播放路径
            showMinimized();//最小化
            ui->fileName->setText(filePath);//更新控件文本
        }
        else
            if(filePath!=""&&filePath.contains(".html")||rx.exactMatch(filePath))//如果不为空，是html(url)
            {
                w.setWindowFlags(Qt::FramelessWindowHint);//无边框
                w.setWindowFlags(Qt::Dialog);//提升为顶级窗口
                w.StartPlay(filePath);//将控件文本传入播放路径
                SetCursorPos(window()->pos().x(), window()->pos().y()+50);  //屏幕坐标
                mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);//瞎点一下，让系统响应
                showMinimized();//最小化
                ui->fileName->setText(filePath);//更新控件文本
            }
            else
                QMessageBox::warning(this,QString::fromLocal8Bit("蛤？"),QString::fromLocal8Bit("<h1>没有选择<font color='red'>媒体</font>！</h1>"));//迷之警告

}
void MainWindow::closeEvent(QCloseEvent *event)//重写关闭事件
{
    v.~VideoWindow();//关闭vidioewindow，不这么写的话会导致窗口一直挂着
    g.~GifWindow();//关闭gifwindow，不这么写的话会导致窗口一直挂着
    w.deleteLater();//关闭webwindow，不这么写的话会导致窗口一直挂着
    event->accept();
}

void MainWindow::on_FileOpen_clicked()
{
    //文件选取
    QString media =QFileDialog::getOpenFileName(this,QString::fromLocal8Bit("选择作为壁纸的视频"),"",QString::fromLocal8Bit("媒体文件(*.mp4 *.avi *.mkv *.gif *.html)"));
    ui->PathEdit->setText(media);
}

void MainWindow::on_checkBox_stateChanged(int arg1)
{
    if(arg1==Qt::Checked)//被选中
    {
        v.PlayerState = QMediaPlaylist::CurrentItemInLoop;//循环播放
        if(v.player->state()==QMediaPlayer::StoppedState)
            v.player->play();
        g.PlayerState = QMediaPlaylist::CurrentItemInLoop;//循环播放
        if(g.filePath!="")//不为空
        {
            g.movie->setPaused(false);
            g.movie->start();//重置播放
        }
    }
    else
    {
        v.PlayerState = QMediaPlaylist::CurrentItemOnce;//播一次
        g.PlayerState = QMediaPlaylist::CurrentItemOnce;//播一次
    }
}
