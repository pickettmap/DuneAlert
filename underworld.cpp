#include "underworld.h"
#include <QGraphicsScene>
#include "bullet.h"

Underworld::Underworld(QGraphicsScene * scene)
{
    QImage *img = new QImage(":/images/battlebackground.jpg");
    *img = img->scaled(100,100,Qt::KeepAspectRatioByExpanding);
    QBrush bg_brush(*img);
    scene ->setBackgroundBrush(bg_brush);

    for (int i =0; i < 50; i ++) {
        Bullet *b = new Bullet();
        scene->addItem(b);
    }
}
