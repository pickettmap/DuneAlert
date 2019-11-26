#include "box.h"
#include <QPainter>

Box::Box(int x, int y, int width, int height)
{
    x_ = x;
    y_ = y;
    width_ = width;
    height_ = height;

}

QRectF Box::boundingRect() const
{
    return QRectF(x_,y_, width_, width_);
}

/*
Coded By: Mikayla Pickett
Function: shape
Params: none
Desc: sets graph as square
Returns: QPainterPath
*/
QPainterPath Box::shape() const
{
    QPainterPath path;
    path.addRect(x_,y_,width_,width_);
    return path;
}

/*
Coded By: Mikayla Pickett
Function: Paint
Params: QPainter, QStyleOptionGraphicsItem, QWidget
Desc: allows cell to be drawn
Returns: void
*/
void Box::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QBrush b = painter->brush();
    QColor c = QColor(Qt::GlobalColor::white);
    painter->setBrush(Qt::NoBrush);
    painter->setPen(c);
    //painter->setBrush(Qt::NoBrush);
    painter->drawRect(QRect(this->x_, this->y_, this-> width_, this-> height_));
    painter->setBrush(b);
}
