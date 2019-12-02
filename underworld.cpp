#include "underworld.h"
#include <QGraphicsScene>
#include <QPainter>
#include "bullet.h"
#include "containingbox.cpp"
#include "player.h"
#include <QTimer>
#include "enemy.h"
#include <QDebug>
#include "healthbar.h"

//TODO constructor needs to be able to instantiate enemy
Underworld::Underworld(QGraphicsScene * main_scene)
{
    this->scene = main_scene;
    QImage *img = new QImage(":/images/battlebackground.jpg");
    *img = img->scaled(100,100,Qt::KeepAspectRatioByExpanding);
    QBrush bg_brush(*img);
    scene ->setBackgroundBrush(bg_brush);

    qDebug() << scene->width();
    qDebug() << scene->height();

    QPixmap sprite = QPixmap(":/images/heart.png");
    sprite = sprite.scaled(50,50,Qt::KeepAspectRatio);
    Bounds bound = {20, 200, 570, 450};
    player *heart = new player(sprite, 5, 10, bound);
    heart->setFlag(QGraphicsItem::ItemIsFocusable,true);
    heart->setPos(200, 300);
    scene->addItem(heart);
    heart->setFocus();

    ContainingBox *b = new ContainingBox(20, 200, 600, 300, nullptr);
    scene->addItem(b);
    connect(this, &Underworld::OnBulletFired, this, &Underworld::FireBullet);

    QPixmap enemy_sprite = QPixmap(":/images/Gr8.png");
    enemy_sprite = enemy_sprite.scaled(300, 300, Qt::KeepAspectRatio);
    Enemy *e = new Enemy(enemy_sprite, 5, 10, bound);
    e->setPos(150, -150);
    scene->addItem(e);

    HealthBar *h = new HealthBar();
    scene->addItem(h);



    std::vector<AttackPattern> a;


    int current_delay = 200;
    for (int i = 0; i < 50; i ++) {
        current_delay += 300;
        AttackPattern p = {current_delay, 20 + i * 5, 200, Direction::S};
        a.push_back(p);
    }

    ProcessAttackPattern(a);
}

//Function:
void Underworld::ProcessAttackPattern(std::vector<AttackPattern> s) {
    for (size_t i = 0; i < s.size(); i ++) {
        QTimer::singleShot(s[i].delay, [=](){
            FireBullet(s[(int)i].x, s[(int)i].y);
        });
    }
}

void Underworld::FireBullet(int x, int y) {
        Bullet *b = new Bullet(x, y, Direction::S);
        scene->addItem(b);
}
