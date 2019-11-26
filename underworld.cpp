#include "underworld.h"
#include <QGraphicsScene>
#include <QPainter>
#include "bullet.h"
#include "box.cpp"
#include "underworldplayer.h"

Underworld::Underworld(QGraphicsScene * scene)
{

    QImage *img = new QImage(":/images/battlebackground.jpg");
    *img = img->scaled(100,100,Qt::KeepAspectRatioByExpanding);
    QBrush bg_brush(*img);
    scene ->setBackgroundBrush(bg_brush);

    QPixmap sprite = QPixmap(":/images/heart.png");
    sprite = sprite.scaled(50,50,Qt::KeepAspectRatio);
    UnderworldPlayer *heart = new UnderworldPlayer(sprite);
    heart->setFlag(QGraphicsItem::ItemIsFocusable,true);
    scene->addItem(heart);
    heart->setFocus();

//    Bullet *b = new Bullet();
//    scene->addItem(b);
    Box *b = new Box(20, 200, 800, 400);
    scene->addItem(b);


}
