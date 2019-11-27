#include "underworld.h"
#include <QGraphicsScene>
#include <QPainter>
#include "bullet.h"
#include "containingbox.cpp"
#include "player.h"
#include <QTimer>

Underworld::Underworld(QGraphicsScene * main_scene)
{
    this->scene = main_scene;
    QImage *img = new QImage(":/images/battlebackground.jpg");
    *img = img->scaled(100,100,Qt::KeepAspectRatioByExpanding);
    QBrush bg_brush(*img);
    scene ->setBackgroundBrush(bg_brush);

    QPixmap sprite = QPixmap(":/images/heart.png");
    sprite = sprite.scaled(50,50,Qt::KeepAspectRatio);
    player *heart = new player(sprite, 5, 10);
    heart->setFlag(QGraphicsItem::ItemIsFocusable,true);
    scene->addItem(heart);
    heart->setFocus();

    ContainingBox *b = new ContainingBox(20, 200, 800, 400);
    scene->addItem(b);

    ExampleAttackPattern();
    FireBullet();
}

void Underworld::ExampleAttackPattern() {
    QTimer * timer = new QTimer(this);
    connect(timer,&QTimer::timeout, this, &Underworld::FireBullet);
    timer->start(200);
}

void Underworld::FireBullet() {
    Bullet *b = new Bullet(20, 200, Direction::S);
    scene->addItem(b);
}
