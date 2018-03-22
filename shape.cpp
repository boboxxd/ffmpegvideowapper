#include "shape.h"
#include <cmath>
static void drawLine(QPainter *painter,QPoint begin,QPoint end)
{
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->drawLine(begin,end);
}

void Shape::setStart(QPoint s)
{
    start=s;
    if(pointlist.isEmpty())
    {
        pointlist.append(start);
    }
    pointlist.first()=start;
}

void Shape::setEnd(QPoint e)
{
    if(pointlist.size()>1)
    {
        pointlist.last()=e;
        end=e;
    }else
    {
        pointlist.append(e);
        end=e;
    }
}

QPoint Shape::startPoint()
{
    return pointlist.constFirst();
}

QPoint Shape::endPoint()
{
    return pointlist.constLast();
}

//------------------------------------------------------------------------------
void Arrow::paint(QPainter *painter)
{
    painter->setRenderHint(QPainter::Antialiasing, true);
    int x1 = startPoint().x();                                     //取points[0]起点的x
    int y1 = startPoint().y();                                     //取points[0]起点的y
    int x2 = endPoint().x();                                       //取points[count-1]终点的x
    int y2 = endPoint().y();                                       //取points[count-1]终点的y
    int l = 10.0;                                           //箭头的长度
    int a = 1;                                            //箭头与线段角度
    int x3 = x2 - l * cos(atan2((y2 - y1) , (x2 - x1)) - a);//计算箭头的终点（x3,y3）
    int y3 = y2 - l * sin(atan2((y2 - y1) , (x2 - x1)) - a);
    int x4 = x2 - l * sin(atan2((x2 - x1) , (y2 - y1)) - a);//计算箭头的终点（x4,y4）
    int y4 = y2 - l * cos(atan2((x2 - x1) , (y2 - y1)) - a);
    drawLine(painter,QPoint(x2,y2),QPoint(x3,y3));                                 //绘制箭头(x2,y2,x3,y3)
    drawLine(painter,QPoint(x2,y2),QPoint(x4,y4));                                 //绘制箭头(x2,y2,x4,y4)
    drawLine(painter,startPoint(),endPoint());                                   //绘制主干箭头(begin,end)
}

void Rect::paint(QPainter *painter)
{
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->drawRect(startPoint().x(), startPoint().y(),
                     endPoint().x() - startPoint().x(), endPoint().y() - startPoint().y());
}

void Polygon::paint(QPainter *painter)
{
    painter->setRenderHint(QPainter::Antialiasing, true);
    for(int i=0;i<pointlist.size()-1;i++)
        drawLine(painter,pointlist[i],pointlist[i+1]);

}

void Polygon::drawLastLine(QPainter *painter)
{
    painter->setRenderHint(QPainter::Antialiasing, true);
    drawLine(painter,pointlist.constLast(),pointlist.constFirst());
}



