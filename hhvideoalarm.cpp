#include "hhvideoalarm.h"
#include <QDebug>
HHVideoAlarm::HHVideoAlarm()
    :QObject(),islogin(false),m_ip(QString()),m_port(30666),callback(new HHCallback()),client(nullptr)
{
    qDebug()<<"HHVideoAlarm::HHVideoAlarm()";
}

HHVideoAlarm::~HHVideoAlarm()
{
    qDebug()<<"HHVideoAlarm::~HHVideoAlarm()";
    delete callback;
}

void HHVideoAlarm::RecieveAlarm(const QVariant& data)
{
    emit SendAlarm(data);
}

void HHVideoAlarm::setLoginInfo(const QString &ip,int port)
{
    m_ip=ip;
    m_port=port;
}


void HHVideoAlarm::Login()
{

    client = HHClientAPI_Create(callback);
    connect(callback,&HHCallback::SendAlarm,this,&HHVideoAlarm::RecieveAlarm);
    HHResult ret = client->Login(m_ip.toStdString(),m_port);
    if(ret != OK){
        emit Error(CONNECTERROR,"报警服务器登录失败!");
    }else
    {
        islogin=true;
    }
}

void HHVideoAlarm::LogOut()
{
    qDebug()<<"void HHVideoAlarm::LogOut()";
    if(islogin)
    {
        qDebug()<<"HHClient_Destroy(client);";
        HHClient_Destroy(client);
        islogin=false;
    }
}

void HHCallback::onAlarm(const HHAlarm &alarm)
{
    QVariant data;
    data.setValue(alarm);
    emit SendAlarm(data);
}

QString HHVideoAlarm::cartypeString(HHAlarm alarm)
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
