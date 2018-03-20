#include "hhvideowidget.h"
#include <QPainter>
#include <QMouseEvent>
#include <QMessageBox>
#include <QDebug>
#include <iostream>
HHVideoWidget::HHVideoWidget(QWidget *parent)
    :QOpenGLWidget(parent),m_stream(nullptr),m_alarm(nullptr),image(QImage()),isshow(false)
{
    qDebug()<<"HHVideoWidget::HHVideoWidget(QWidget *parent)";
    setAttribute(Qt::WA_DeleteOnClose);
}

void HHVideoWidget::setStream(HHVideoStream *stream)
{
    if(stream==nullptr)
    {
        std::cout<<"视频流不能为空!"<<std::endl;
        return;
    }

    m_stream=stream;
    connect(m_stream,&HHVideoStream::GetImage,this,&HHVideoWidget::ShowImage);
}

void HHVideoWidget::setAlarm(HHVideoAlarm *alarm)
{
    if(alarm==nullptr)
    {
        std::cout<<"报警流不能为空!"<<std::endl;
        return;
    }

    m_alarm=alarm;
    connect(m_alarm,&HHVideoAlarm::SendAlarm,this,&HHVideoWidget::RecieveAlarm);
}

HHVideoWidget::~HHVideoWidget()
{
    qDebug()<<"HHVideoWidget::~HHVideoWidget()";

}

void HHVideoWidget::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event);
    qDebug()<<"void HHVideoWidget::closeEvent(QCloseEvent *event)";
    disconnectFromAlarm();
    disconnectFromStream();
}

void HHVideoWidget::ShowImage(const QImage& img)
{
    image=img;
    update();
}

void HHVideoWidget::setisshow()
{
    isshow=false;
}

void HHVideoWidget::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
    if(image.isNull())
        return;
    /**
        draw box on image
    **/
    QPainter painter;
    if(isshow)
    {
        painter.begin(&image);
        painter.setPen(QPen(Qt::green,4));
        painter.drawRect(m_rect);
        QFont font("宋体",25,QFont::Bold,true);
        painter.setFont(font);
        painter.drawText(m_rect.topLeft().x(),m_rect.topLeft().y()-10,m_type);
        painter.end();
    }

    /**
        draw image to Widget
    **/
    painter.begin(this);
    QImage tmp=image.scaled(this->width(),this->height(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
    int posx=(this->width()-tmp.width())/2;
    int posy=(this->height()-tmp.height())/2;
    painter.drawImage(posx,posy,tmp);
    painter.end();
}


void HHVideoWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
    {
        if(isFullScreen() == false)
        {
            setWindowFlags(Qt::Window);
            showFullScreen();
        }else
        {
            setWindowFlags(Qt::SubWindow);
            showNormal();
        }
    }
}

void HHVideoWidget::RecieveAlarm(const QVariant& data)
{
    HHAlarm alarm=data.value<HHAlarm>();
    m_rect=QRect(alarm.coordinate[0],alarm.coordinate[1],alarm.coordinate[2],alarm.coordinate[3]);
    m_type=HHVideoAlarm::cartypeString(alarm);
    isshow=true;
    QTimer::singleShot(2000, this, SLOT(setisshow()));
    update();
}

void HHVideoWidget::disconnectFromStream()
{
    disconnect(m_stream,&HHVideoStream::GetImage,this,&HHVideoWidget::ShowImage);
}

void HHVideoWidget::disconnectFromAlarm()
{
    disconnect(m_alarm,&HHVideoAlarm::SendAlarm,this,&HHVideoWidget::RecieveAlarm);
}

