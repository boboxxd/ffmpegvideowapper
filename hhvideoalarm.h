#ifndef HHVIDEOALARM_H
#define HHVIDEOALARM_H

#include <QObject>
#include <QVariant>
#include "HHClient.hpp"
using namespace hhclient;
class HHCallback: public QObject,public HHlientCallback
{
    Q_OBJECT
        void onAlarm(const HHAlarm &alarm);
    signals:
        void SendAlarm(QVariant);
};

class HHVideoAlarm : public QObject
{
    Q_OBJECT
public:
    enum HHVideoAlarmError
    {
        CONNECTERROR
    };

    HHVideoAlarm(QObject *parent = nullptr);
    ~HHVideoAlarm();
    void setLoginInfo(QString ip,int port);
signals:
    void SendAlarm(QVariant);
    void Error(HHVideoAlarmError,const QString&);
public slots:
    void RecieveAlarm(QVariant);
    void Login();
    void LogOut();   
private:
    bool islogin;
    QString m_ip;
    int m_port;
    HHCallback *callback;
    HHClientAPI *client;
};
Q_DECLARE_METATYPE(HHAlarm)
#endif // HHVIDEOALARM_H
