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

    if(desktopWnd) SetParent((HWND)v.winId(), desktopWnd);//设置父窗体为桌面
    //v.setWindowState(Qt::WindowMaximized);//最大化
    if(ui->PathEdit->toPlainText()!="")//如果不为空
    {
        v.setWindowFlags(Qt::FramelessWindowHint);//无边框
        v.setWindowFlags(Qt::Dialog);//提升为顶级窗口
        v.showFullScreen();//showtime！全屏！
        v.StartPlay(ui->PathEdit->toPlainText());//将控件文本传入播放路径
    }
    else
        QMessageBox::warning(this,"蛤？","<h1>没有选择<font color='red'>媒体</font>！</h1>");//迷之警告

}
void MainWindow::closeEvent(QCloseEvent *event)//重写关闭事件
{
    v.~VideoWindow();//关闭vidioewindow，不这么写的话会导致窗口一直挂着
    ShellExecuteA(NULL,"open","cmd.exe","taskkill /f /im explorer.exe & start explorer.exe",NULL,SW_HIDE);//重启任务管理器
    event->accept();
}

void MainWindow::on_FileOpen_clicked()
{
    //文件选取
    QString media =QFileDialog::getOpenFileName(this,tr("选择作为壁纸的视频"),"/home",tr("视频文件(*.mp4 *.avi)"));
    ui->PathEdit->setText(media);
}

void MainWindow::on_checkBox_stateChanged(int arg1)
{
    if(arg1==Qt::Checked)//被选中
    {
        v.PlayerState = QMediaPlaylist::CurrentItemInLoop;//循环播放
        if(v.player->state()==QMediaPlayer::StoppedState)
            v.player->play();
    }
    else
        v.PlayerState = QMediaPlaylist::CurrentItemOnce;//播一次
}
