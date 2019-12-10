#include "statsdisplay.h"
#include <QPainter>
#include <QPen>

StatsDisplay::StatsDisplay(int x, int y, std::string name, int max_health, int current_health, int gold, int damage, QColor box_color)
{
    x_ = x;
    y_ = y;
    player_name_ = name;
    max_health_ = max_health;
    current_health_ = current_health;
    gold_ = gold;
    box_color_ = box_color;
    damage_ = damage;
}

QRectF StatsDisplay::boundingRect() const
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
QPainterPath StatsDisplay::shape() const
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
void StatsDisplay::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    int distance_between = 20;
    QBrush b = painter->brush();
    painter->setPen(Qt::GlobalColor::white);
    QString title = QString::fromStdString(player_name_ + " Stats");
    painter->drawText(QPoint(this->x_, this->y_ - 5), title);
    int current_y = this->y_;
    int shifted_x = this->x_ + 10;

    current_y += distance_between;
    QString health = QString::fromStdString("Health: " + std::to_string(current_health_) + "/" + std::to_string(max_health_));
    painter->drawText(QPoint(shifted_x, current_y), health);

    current_y += distance_between;
    QString damage = QString::fromStdString("Damage: " + std::to_string(damage_));
    painter->drawText(QPoint(shifted_x, current_y), damage);


    current_y += distance_between;
    QString gold = QString::fromStdString("Gold: " + std::to_string(gold_));
    painter->drawText(QPoint(shifted_x, current_y), gold);


    painter->setPen(QPen(box_color_, 2));
    painter->drawRect(QRect(this->x_, this->y_, this-> width_, height_));
    painter->setBrush(b);
}

void StatsDisplay::StatsUpdated(int max_health, int current_health, int gold, int damage) {
    max_health_ = max_health;
    current_health_ = current_health;
    gold_ = gold;
    damage_ = damage;
}
