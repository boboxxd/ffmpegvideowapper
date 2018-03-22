#ifndef HHVIDEOMARKWIDGET_H
#define HHVIDEOMARKWIDGET_H

#include <QOpenGLWidget>
#include "hhshapeitem.h"
#include "shape.h"
class HHVideoMarkWidget : public QOpenGLWidget
{
public:
    HHVideoMarkWidget(QWidget *parent=nullptr);
    void paintEvent(QPaintEvent *e);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void setCurrentShape(Shape::Code s);
    void setCurrentType(AreaType type);

public slots:
    void RecieveImage(const QImage&);

private:
    Shape::Code m_currShapeCode;
    AreaType m_type;
    HHShapeItem m_item;
    bool m_perm;
    QList<HHShapeItem> m_shapeList;
};

#endif // HHVIDEOMARKWIDGET_H
