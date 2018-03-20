#include "widget.h"
#include <QPainter>
#include <QMouseEvent>
#include <QMessageBox>
#include <QHBoxLayout>

#include <QThread>
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent)
{ 
    qDebug()<<"Widget::Widget(QWidget *parent)";
    HHVideoStream *stream=new HHVideoStream;
    stream->setUrl("rtsp://admin:ad53937301@122.192.0.173:554/h264/ch1/main/av_stream");
    videowidget=new HHVideoWidget(this);
    videowidget->setStream(stream);
    alarm=new HHVideoAlarm;
    videowidget->setAlarm(alarm);
    alarm->setLoginInfo("122.192.0.173",30666);
    alarm->Login();
    stream->startStream();

    QHBoxLayout *layout=new QHBoxLayout(this);

    btn1=new QPushButton(this);
    btn2=new QPushButton(this);
    btn1->setText("disconnect");
    btn2->setText("connect");
    connect(btn1,&QPushButton::clicked,stream,&HHVideoStream::stopStream);
    connect(btn2,&QPushButton::clicked,stream,&HHVideoStream::startStream);
    connect(btn1,&QPushButton::clicked,alarm,&HHVideoAlarm::LogOut);
    connect(btn2,&QPushButton::clicked,alarm,&HHVideoAlarm::Login);

    connect(stream,&HHVideoStream::Error,this,&Widget::HandleHHVideoStreamError);
    connect(alarm,&HHVideoAlarm::Error,this,&Widget::HandleHHVideoAlarmError);

    connect(this,&Widget::destroyed,stream,&HHVideoStream::deleteLater);
    connect(this,&Widget::destroyed,alarm,&HHVideoAlarm::deleteLater);
    connect(this,&Widget::destroyed,videowidget,&HHVideoWidget::deleteLater);


    layout->addWidget(btn1);
    layout->addWidget(btn2);
    layout->addWidget(videowidget);
    layout->setStretch(0,1);
    layout->setStretch(1,1);
    layout->setStretch(2,8);
    videowidget->resize(this->width(),this->height());
    btn1->show();
    btn2->show();
    videowidget->show();
}

void Widget::HandleHHVideoStreamError(HHVideoStream::HHVideoStreamError,const QString& msg )
{
    QMessageBox::information(this, "error", msg, QMessageBox::Yes );
}

void Widget::HandleHHVideoAlarmError(HHVideoAlarm::HHVideoAlarmError,const QString& msg )
{
    QMessageBox::information(this, "error", msg, QMessageBox::Yes );
}


void Widget::closeEvent(QCloseEvent *event)
{
    qDebug()<<endl;
    qDebug()<<"正在关闭应用程序...........";
    qDebug()<<"void Widget::closeEvent(QCloseEvent *event)";
    close();
}

Widget::~Widget()
{
    qDebug()<<"Widget::~Widget()";
    delete videowidget;
    videowidget=nullptr;
    delete alarm;
    alarm=nullptr;
    delete stream;
    stream=nullptr;
}
