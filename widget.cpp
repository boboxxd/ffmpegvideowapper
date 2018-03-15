#include "widget.h"
#include <QPainter>
#include <QMouseEvent>
#include <QMessageBox>
#include <QHBoxLayout>

Widget::Widget(QWidget *parent) :
    QWidget(parent)
{ 
    HHVideoStream *stream=new HHVideoStream;
    stream->setUrl("rtsp://admin:ad53937301@122.192.0.173:554/h264/ch1/main/av_stream");
    videowidget=new HHVideoWidget(0,this);
    videowidget->setStream(stream);
    connect(stream,&HHVideoStream::GetImage,videowidget,&HHVideoWidget::ShowImage);
    connect(stream,&HHVideoStream::Error,videowidget,&HHVideoWidget::handleError);
    stream->startStream();
    QHBoxLayout *layout=new QHBoxLayout(this);
    layout->addWidget(videowidget);
    videowidget->resize(this->width(),this->height());
    videowidget->show();
}

Widget::~Widget()
{
    delete videowidget;
    delete stream;
}
