#ifndef HEALTHBAR_H
#define HEALTHBAR_H

#include <QGraphicsRectItem>


class HealthBar :  public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    HealthBar(int x, int y, int width, int height, int max_health);
    //Would be great if this was a slot and it could be triggered

public slots:
    void ChangeHealth(int change);

private:
    int max_health_points;
    int current_health_points;
    int width_;
    int height_;
};

#endif // HEALTHBAR_H
