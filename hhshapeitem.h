#ifndef HHSHAPEITEM_H
#define HHSHAPEITEM_H
#include "shape.h"
#include <memory>
#include <QColor>
#include <QPainter>

enum AreaType{
    HANDLEAREA,//处理区域
    ALARMAREA, //报警区域
    ARROWTIP   //箭头提示出入
};


class HHShapeItem
{
public:
    using ShapePtr=std::shared_ptr<Shape>;
    HHShapeItem()=default;
    HHShapeItem(ShapePtr,AreaType);
    bool isNULL();
    AreaType areatype();//返回区域类别
    QColor color();//返回区域颜色
    void setStartPoint(const QPoint&);
    void setEndPoint(const QPoint&);
    void draw(QPaintDevice*);

private:
    void setcolor();
    ShapePtr m_shape;//包含着画图方法
    AreaType m_type;
    QColor m_color;
};

#endif // HHSHAPEITEM_H
