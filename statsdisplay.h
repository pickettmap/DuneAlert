#ifndef STATSDISPLAY_H
#define STATSDISPLAY_H
#include <QObject>
#include <QGraphicsItem>


class StatsDisplay: public QObject, public QGraphicsItem
{
public:
    StatsDisplay(int x, int y, std::string name, int max_health, int current_health, int gold, int damage, QColor box_color_);
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

public slots:
    void StatsUpdated(int max_health, int current_health, int gold, int damage);

private:
    int width_ = 100;
    int height_ = 80;
    int x_;
    int y_;
    int current_health_;
    int max_health_;
    int gold_;
    int damage_;
    QColor box_color_;
    std::string player_name_;
};

#endif // STATSDISPLAY_H
