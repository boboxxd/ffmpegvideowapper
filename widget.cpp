#include "widget.h"
#include "ui_widget.h"
#include <QPainter>
#include <QMouseEvent>
#include <QMessageBox>
#include <QHBoxLayout>

Widget::Widget(QWidget *parent) :
    QWidget(parent)
{
    QHBoxLayout *layout=new QHBoxLayout(this);
    HHVideoStream *stream=new HHVideoStream;
    stream->setUrl("rtsp://admin:ad53937301@122.192.0.173:554/h264/ch1/main/av_stream");
    videowidget=new HHVideoWidget(stream,this);
    connect(stream,&HHVideoStream::GetImage,videowidget,&HHVideoWidget::GetImage);
    connect(stream,&HHVideoStream::Error,videowidget,&HHVideoWidget::handleError);
    stream->startStream();
    layout->addWidget(videowidget);
    videowidget->resize(this->width(),this->height());
    videowidget->show();
}



Widget::~Widget()
{
    delete videowidget;
    delete stream;
}
