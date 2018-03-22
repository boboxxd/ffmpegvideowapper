#include "hhvideomarkwidget.h"
#include <QDebug>
HHVideoMarkWidget::HHVideoMarkWidget(QWidget *parent)
    :QOpenGLWidget(parent), m_currShapeCode(Shape::Arrow), m_item(HHShapeItem()), m_perm(false)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setCurrentShape(Shape::Code::Rect);
    setCurrentType(AreaType::HANDLEAREA);
}

void HHVideoMarkWidget::setCurrentShape(Shape::Code s)
{
    if(s != m_currShapeCode) {
        m_currShapeCode =s;
    }
}


void HHVideoMarkWidget::setCurrentType(AreaType type)
{
    if(type != m_type) {
        m_type =type;
    }
}


void HHVideoMarkWidget::paintEvent(QPaintEvent *e)
{
    QOpenGLWidget::paintEvent(e);
    QPainter painter(this);
    painter.setBrush(Qt::white);
    painter.drawRect(0, 0, size().width(), size().height());
    painter.end();

    foreach(HHShapeItem item, m_shapeList) {
        item.draw(this);
    }

    if(m_item.isNULL()) {
        qDebug()<<"draw shape";
        m_item.draw(this);
    }
}


void HHVideoMarkWidget::mousePressEvent(QMouseEvent *event)
{
    switch(m_currShapeCode)
    {
        case Shape::Arrow:
        {
            HHShapeItem::ShapePtr shape=std::shared_ptr<Arrow>(new Arrow);
            m_item=HHShapeItem(shape,m_type);
            break;
        }

        case Shape::Rect:
        {
            qDebug()<<"void HHVideoMarkWidget::mousePressEvent(QMouseEvent *event)";
            qDebug()<<"in case Shape::Rect";
            HHShapeItem::ShapePtr shape=std::shared_ptr<Rect>(new Rect);
            m_item=HHShapeItem(shape,m_type);
            break;
        }

        case Shape::Polygon:
        {
            HHShapeItem::ShapePtr shape=std::shared_ptr<Polygon>(new Polygon);
            m_item=HHShapeItem(shape,m_type);
            break;
        }
    }

    if(m_item.isNULL()){
        m_perm = false;
        m_shapeList<<m_item;
        m_item.setStartPoint(event->pos());
        m_item.setEndPoint(event->pos());
    }
}


void HHVideoMarkWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(m_item.isNULL() && !m_perm) {
        m_item.setEndPoint(event->pos());
        update();
    }
}


void HHVideoMarkWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if(m_currShapeCode!=Shape::Polygon)
    {
        //非多边形两点确定一个图形
        m_perm = true;
    }else
    {
         //多边形有左击结束标志

    }
     update();
}

void HHVideoMarkWidget::RecieveImage(const QImage&)
{

}
