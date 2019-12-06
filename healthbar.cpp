#include "healthbar.h"
#include <QBrush>
#include <QDebug>

HealthBar::HealthBar(int x, int y, int width, int height, int max_health)
{
    setRect(x, y, width, height);
    setBrush(QBrush(Qt::red));
    current_health_points = max_health;
    max_health_points = max_health;
    width_ = width;
    height_ = height;
}

void HealthBar::ChangeHealth(int change) {
    current_health_points += change;
    double percent = double(current_health_points) / double(max_health_points);
    setRect(rect().x(),rect().y(),percent * width_, height_);
}



