#ifndef HHVIDEOWIDGET_H
#define HHVIDEOWIDGET_H

#include <QObject>
#include <QOpenGLWidget>
#include "hhvideostream.h"
#include <QImage>
#include <QLabel>
class HHVideoWidget : public QOpenGLWidget
{
    Q_OBJECT
public:
    HHVideoWidget(HHVideoStream *stream=0,QWidget *parent=0);
    void paintEvent(QPaintEvent *e);
    void mouseDoubleClickEvent(QMouseEvent *e);
    ~HHVideoWidget();
public slots:
    void ShowImage(QImage);
    void handleError(HHVideoStream::HHVideoStreamError,const QString& );
private:
    HHVideoStream *m_stream;
    QImage image;
    int m_width,m_height;
};

#endif // HHVIDEOWIDGET_H
