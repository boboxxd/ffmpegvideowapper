#ifndef SHAPE_H
#define SHAPE_H
#include <QPoint>
#include <QPainter>
#include <QList>

using QPointList=QList<QPoint>;

class Shape
{
public:
    enum Code {
        Rect,
        Arrow,//非区域，紧作提示
        Polygon
    };

    Shape()=default;
    void setStart(QPoint s);
    void setEnd(QPoint e);
    QPoint startPoint();
    QPoint endPoint();
    void virtual paint(QPainter *painter) = 0;
protected:
    QPointList pointlist;
    QPoint start,end;
};


class Arrow : public Shape
{
public:
    Arrow()=default;
    void paint(QPainter *painter);
};

class Rect : public Shape
{
public:
    Rect()=default;
    void paint(QPainter *painter);
};

class Polygon : public Shape
{
public:
    Polygon()=default;
    void paint(QPainter *painter);
    void drawLastLine(QPainter *painter);
};


#endif // SHAPE_H
