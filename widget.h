#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "hhvideowidget.h"

class Widget : public QWidget
{
    Q_OBJECT
public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
private:
    HHVideoWidget *videowidget;
    HHVideoStream *stream;

};

#endif // WIDGET_H
