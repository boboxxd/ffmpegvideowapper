#ifndef HHVIDEOWIDGET_H
#define HHVIDEOWIDGET_H

#include <QObject>
#include <QOpenGLWidget>
#include "hhvideostream.h"
#include "hhvideoalarm.h"
#include <QImage>
#include <QVariant>
#include <QRect>
#include <QTimer>

class HHVideoWidget : public QOpenGLWidget
{
    Q_OBJECT
public:
    HHVideoWidget(HHVideoStream *stream=0,QWidget *parent=0);
    void setStream(HHVideoStream *stream);
    void setAlarm(HHVideoAlarm *alarm);
    void paintEvent(QPaintEvent *e);
    void mouseDoubleClickEvent(QMouseEvent *e);
    ~HHVideoWidget();
    static QString cartypeString(HHAlarm alarm);
public slots:
    void ShowImage(QImage);
    void RecieveAlarm(QVariant);
private slots:
    void setisshow();
private:
    HHVideoStream *m_stream;
    HHVideoAlarm *m_alarm;
    QImage image;
    int m_width,m_height;

    QRect m_rect;
    QString m_type;
    bool isshow;
};

#endif // HHVIDEOWIDGET_H
