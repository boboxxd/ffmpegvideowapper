#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "hhvideowidget.h"
#include "hhvideoalarm.h"
class Widget : public QWidget
{
    Q_OBJECT
public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
public slots:
    void HandleHHVideoStreamError(HHVideoStream::HHVideoStreamError,const QString& msg );
    void HandleHHVideoAlarmError(HHVideoAlarm::HHVideoAlarmError,const QString& msg ) ;
private:
    HHVideoWidget *videowidget;
    HHVideoStream *stream;
    HHVideoAlarm *alarm;
};

#endif // WIDGET_H
