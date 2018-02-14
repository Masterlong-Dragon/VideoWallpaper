#ifndef VIDEO_H
#define VIDEO_H

#include <QObject>
#include <QWidget>
#include <QDialog>
#include <QLineEdit>

class Video:public QDialog
{
    Q_OBJECT
public:
    Video(QWidget *parent = 0);
    ~Video();


};

#endif // VIDEO_H
