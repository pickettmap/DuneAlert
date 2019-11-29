#include "healthbar.h"
#include <QBrush>

HealthBar::HealthBar()
{
    setRect(100, -300,400,50);
    setBrush(QBrush(Qt::red));
}
