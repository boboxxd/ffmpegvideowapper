#include "hhvideoalarm.h"
#include <QDebug>
HHVideoAlarm::HHVideoAlarm()
    :QObject(),islogin(false),m_ip(QString()),m_port(30666),callback(nullptr),client(nullptr)
{
    qDebug()<<"HHVideoAlarm::HHVideoAlarm()";
    callback = new HHCallback();
}

HHVideoAlarm::~HHVideoAlarm()
{
    qDebug()<<"HHVideoAlarm::~HHVideoAlarm()";
    delete callback;
    callback=nullptr;
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
