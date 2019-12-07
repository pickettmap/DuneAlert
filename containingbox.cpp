#include "containingbox.h"
#include <QPainter>
#include <QDebug>

ContainingBox::ContainingBox(int x, int y, int width, int height, QColor color, std::string text)
{
    x_ = x;
    y_ = y;
    width_ = width;
    height_ = height;
    color_ = color;
    text_ = text;

}

QRectF ContainingBox::boundingRect() const
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
QPainterPath ContainingBox::shape() const
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
void ContainingBox::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRect rec = QRect(this->x_, this->y_, this-> width_, this-> height_);
    QBrush b = painter->brush();
    QFont q = painter->font();
    q.setPointSize(q.pointSize() * 2);
    painter->setFont(q);
    QString s = QString::fromStdString(text_);
    painter->setPen(color_);
    painter->drawText(rec, Qt::AlignCenter, s);
    painter->drawRect(rec);
    painter->setBrush(b);
}

void ContainingBox::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit onBoxClicked();
}
