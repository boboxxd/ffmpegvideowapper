#include "hhvideoalarm.h"
#include <QDebug>
HHVideoAlarm::HHVideoAlarm(QObject *parent) : QObject(parent)
{
    islogin=false;
}

HHVideoAlarm::~HHVideoAlarm()
{
    LogOut();
    delete callback;
    delete client;
    callback=nullptr;
    client=nullptr;
}

void HHVideoAlarm::RecieveAlarm(QVariant data)
{
    emit SendAlarm(data);
}

void HHVideoAlarm::setLoginInfo(QString ip,int port)
{
    m_ip=ip;
    m_port=port;
}


void HHVideoAlarm::Login()
{
    callback = new HHCallback();
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
    if(islogin)
    {
        qDebug()<<"islogin= "<<islogin;
        HHClient_Destroy(client);
        islogin=false;
        qDebug()<<"islogin= "<<islogin;
    }
}

void HHCallback::onAlarm(const HHAlarm &alarm)
{
    QVariant data;
    data.setValue(alarm);
    emit SendAlarm(data);
}
