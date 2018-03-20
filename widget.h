#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "hhvideowidget.h"
#include "hhvideoalarm.h"
#include <QPushButton>
class Widget : public QWidget
{
    Q_OBJECT
public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    void closeEvent(QCloseEvent *event);
public slots:
    void HandleHHVideoStreamError(HHVideoStream::HHVideoStreamError,const QString& msg );
    void HandleHHVideoAlarmError(HHVideoAlarm::HHVideoAlarmError,const QString& msg ) ;
private:
    HHVideoWidget *videowidget;
    HHVideoStream *stream;
    HHVideoAlarm *alarm;
    QPushButton *btn1,*btn2;
};

#endif // WIDGET_H
