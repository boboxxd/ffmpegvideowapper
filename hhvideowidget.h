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

struct ARect{
    QRect rect;
    QString type;
};

class HHVideoWidget : public QOpenGLWidget
{
    Q_OBJECT
public:
    explicit  HHVideoWidget(QWidget *parent= nullptr);
    void setStream(HHVideoStream *stream);
    void setAlarm(HHVideoAlarm *alarm);
    void paintEvent(QPaintEvent *e) override;
    void mouseDoubleClickEvent(QMouseEvent *e) override;
    void closeEvent(QCloseEvent *event) override;
    void disconnectFromStream();
    void disconnectFromAlarm();
public slots:
    void ShowImage(const QImage&);
    void RecieveAlarm(const QVariant&);
private slots:
    void setisshow();
private:
    HHVideoStream *m_stream;
    HHVideoAlarm *m_alarm;
    QImage image;
    bool isshow;
    ARect m_rect;
    QVector<ARect> m_rects;
    int m_curimageid;
};

#endif // HHVIDEOWIDGET_H
