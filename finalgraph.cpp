#include "finalgraph.h"
#include <QPainter>

/*
Coded By: Zander Louie
Function: Default Graph Constructor
Params: height and (x,y) coord for upper left corner
Desc: Draws a white rectangle
Returns: Graph
*/
FinalGraph::FinalGraph(int height, int x, int y, QColor)
{
    x_ = x;
    y_ = y;
    height_ = height;
    QColor c(Qt::GlobalColor::white);
    color_ = Qt::GlobalColor::blue;
}

/*
Coded By: Zander Louie
Function: BoundingRect
Params: none
Desc: Sets Bounding Rect for graph object
Returns: QRectF
*/
QRectF FinalGraph::boundingRect() const
{
    return QRectF(x_,y_, width_, height_);
}

/*
Coded By: Zander Louie
Function: shape
Params: none
Desc: sets graph as rectangle
Returns: QPainterPath
*/
QPainterPath FinalGraph::shape() const
{
    QPainterPath path;
    path.addRect(x_,y_,width_,height_);
    return path;
}

/*
Coded By: Zander Louie
Function: Paint
Params: QPainter, QStyleOptionGraphicsItem, QWidget
Desc: allows graph to be drawn
Returns: void
*/
void FinalGraph::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget)

    QBrush b = painter->brush();
    painter->setBrush(QBrush(color_));
    //painter->setBrush(Qt::NoBrush);
    painter->drawRect(QRect(this->x_, this->y_, this-> width_, this-> height_));
    painter->setBrush(b);
}
