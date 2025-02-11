#include "healthbar.h"
#include <QBrush>
#include <QDebug>
#include <QPainter>

/*
Function: HealthBar constructor
Params: int x, int y, int width, int height, int max_health, int current_health
Desc: Draws healthbar based on starting position, size, and how much
health there is relative to max health
Returns: HealthBar
*/
HealthBar::HealthBar(int x, int y, int width, int height, int max_health, int current_health)
{
    current_health_points = current_health;
    max_health_points = max_health;
    double percent = double(current_health_points) / double(max_health_points);
    width_ = width * percent;
    original_width = width;
    height_ = height;
    x_ = x;
    y_ = y;
}

/*
Function: ChangeHealth
Params: int change
Desc: Updates healthbar to reflect change in health
Returns: None
*/
void HealthBar::ChangeHealth(int change) {
    current_health_points += change;
    double percent = double(current_health_points) / double(max_health_points);
    width_ = original_width * percent;

}

/*
Function: boundingRect
Params: None
Desc: Sets boundingrect for healthbar
Returns: QRect
*/
QRectF HealthBar::boundingRect() const
{
    return QRectF(x_,y_, width_, height_);
}

/*
Coded By: Mikayla Pickett
Function: shape
Params: none
Desc: sets graph as square
Returns: QPainterPath
*/
QPainterPath HealthBar::shape() const
{
    QPainterPath path;
    path.addRect(x_,y_,width_,height_);
    return path;
}

/*
Coded By: Mikayla Pickett
Function: Paint
Params: QPainter, QStyleOptionGraphicsItem, QWidget
Desc: allows cell to be drawn
Returns: void
*/
void HealthBar::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);

    QBrush b = painter->brush();
    painter->setBrush(QBrush(Qt::GlobalColor::red));
    //painter->setBrush(Qt::NoBrush);
    painter->drawRect(QRect(this->x_, this->y_, this-> width_, this-> height_));
    std::string name = std::to_string(current_health_points) + "/" + std::to_string(max_health_points);
    painter->drawText(QRect(x_, y_, width_, height_), Qt::AlignCenter, QString::fromStdString(name));
    painter->setBrush(b);
}



