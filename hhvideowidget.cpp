#include "hhvideowidget.h"
#include <QPainter>
#include <QMouseEvent>
#include <QMessageBox>
#include <QDebug>
#include <iostream>
HHVideoWidget::HHVideoWidget(QWidget *parent)
    :QOpenGLWidget(parent),isshow(false),m_stream(nullptr),m_alarm(nullptr),image(QImage())
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

 QString HHVideoWidget::cartypeString(HHAlarm alarm)
{
    //     NONE = 0,
    //     TRUCK_CRANE = 1,                //吊车
    //     EXCAVATOR = 2,                  //挖掘机
    //     CEMENT_PUMP_TRUCK = 3,          //水泥泵车
    //     BULLDOZER = 4,                  //推土机
    //     TRUCK_CRANE_WORKING_ARM = 5,    //扬臂吊车
    //     TOWER_CRANE_ARM = 6,            //塔吊
    switch (alarm.car_type)
    {
    case 0:
        return QString(QObject::tr("无"));
    case 1:
        return QString(QObject::tr("吊车"));
    case 2:
        return QString(QObject::tr("挖掘机"));
    case 3:
        return QString(QObject::tr("水泥泵车"));
    case 4:
        return QString(QObject::tr("推土机"));
    case 5:
        return QString(QObject::tr("扬臂吊车"));
    case 6:
        return QString(QObject::tr("塔吊"));
    default:
        return QString(QObject::tr("未定义"));
    }
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
    m_type=cartypeString(alarm);
    isshow=true;
    QTimer::singleShot(3000, this, SLOT(setisshow()));
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

