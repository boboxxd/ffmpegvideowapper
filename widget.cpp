#include "widget.h"
#include <QPainter>
#include <QMouseEvent>
#include <QMessageBox>
#include <QHBoxLayout>
#include <QPushButton>
Widget::Widget(QWidget *parent) :
    QWidget(parent)
{ 
    HHVideoStream *stream=new HHVideoStream;
    stream->setUrl("rtsp://admin:ad53937301@122.192.0.173:554/h264/ch1/main/av_stream");
    videowidget=new HHVideoWidget(0,this);
    videowidget->setStream(stream);
    connect(stream,&HHVideoStream::GetImage,videowidget,&HHVideoWidget::ShowImage);
    connect(stream,&HHVideoStream::Error,videowidget,&HHVideoWidget::HandleError);
    stream->startStream();

    QHBoxLayout *layout=new QHBoxLayout(this);
    QPushButton *btn1,*btn2;
    btn1=new QPushButton(this);
    btn2=new QPushButton(this);
    btn1->setText("disconnect");
    btn2->setText("connect");
    connect(btn1,&QPushButton::clicked,stream,&HHVideoStream::stopStream);
    connect(btn2,&QPushButton::clicked,stream,&HHVideoStream::startStream);
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

Widget::~Widget()
{
    delete videowidget;
    delete stream;
}
