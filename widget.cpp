#include "widget.h"
#include <QPainter>
#include <QMouseEvent>
#include <QMessageBox>
#include <QHBoxLayout>
#include <QPushButton>
#include <QThread>
Widget::Widget(QWidget *parent) :
    QWidget(parent)
{ 
    HHVideoStream *stream=new HHVideoStream;
    stream->setUrl("rtsp://admin:ad53937301@122.192.0.173:554/h264/ch1/main/av_stream");
    videowidget=new HHVideoWidget(0,this);
    videowidget->setStream(stream);
    connect(stream,&HHVideoStream::GetImage,videowidget,&HHVideoWidget::ShowImage);

    alarm=new HHVideoAlarm;
    alarm->setLoginInfo("122.192.0.174",30666);
    alarm->Login();
    connect(alarm,&HHVideoAlarm::SendAlarm,videowidget,&HHVideoWidget::RecieveAlarm);

    stream->startStream();

    QHBoxLayout *layout=new QHBoxLayout(this);
    QPushButton *btn1,*btn2;
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
    QMessageBox::information(NULL, "error", msg, QMessageBox::Yes );
}

void Widget::HandleHHVideoAlarmError(HHVideoAlarm::HHVideoAlarmError,const QString& msg )
{
    QMessageBox::information(NULL, "error", msg, QMessageBox::Yes );
}

Widget::~Widget()
{
    delete videowidget;
    delete stream;
    videowidget=nullptr;
    stream=nullptr;
}
