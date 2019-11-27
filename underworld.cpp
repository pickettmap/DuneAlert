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
    connect(this, &Underworld::OnBulletFired, this, &Underworld::FireBullet);

    ExampleAttackPattern();
}

void Underworld::ExampleAttackPattern() {
    for (int i = 0; i < 50; i ++) {
        QTimer::singleShot(200 + (i * 200), [=](){
            FireBullet(20 + i * 20, 200);
        });
    }
}

void Underworld::FireBullet(int x, int y) {
        Bullet *b = new Bullet(x, y, Direction::S);
        scene->addItem(b);
}
