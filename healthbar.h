#ifndef HEALTHBAR_H
#define HEALTHBAR_H

#include <QGraphicsRectItem>


class HealthBar :  public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    HealthBar(int x, int y, int width, int height, int max_health);
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

public slots:
    void ChangeHealth(int change);

private:
    int max_health_points;
    int current_health_points;
    int original_width;
    int width_;
    int height_;
    int x_;
    int y_;
};

#endif // HEALTHBAR_H
