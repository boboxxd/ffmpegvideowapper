#include "hhshapeitem.h"
#include <QDebug>
HHShapeItem::HHShapeItem(ShapePtr shape,AreaType type)
{
    m_shape=shape;
    m_type=type;
    setcolor();
}

void HHShapeItem::setcolor()
{
    qDebug()<<"void HHShapeItem::setcolor()";
    qDebug()<<m_type;
    switch(m_type)
    {
    case HANDLEAREA:
        m_color=QColor(Qt::blue);
        break;
    case ALARMAREA :
        m_color=QColor(Qt::red);
        break;
    case ARROWTIP:
        m_color=QColor(Qt::green);
        break;
    default:
          break;
    }
    qDebug()<<m_color;
}

bool HHShapeItem::isNULL()
{
    return (m_shape)?true:false;
}

AreaType HHShapeItem::areatype()
{
    return m_type;
}

QColor HHShapeItem::color()
{
    return m_color;
}

void HHShapeItem::setStartPoint(const QPoint &p)
{
    m_shape->setStart(p);
}

void HHShapeItem::setEndPoint(const QPoint &p)
{
    m_shape->setEnd(p);
}

void HHShapeItem::draw(QPaintDevice *device)
{
    QPainter painter(device);
    painter.setPen(QPen(m_color,3));
    m_shape->paint(&painter);
    painter.end();
}
