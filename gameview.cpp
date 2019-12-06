#include "gameview.h"
#include "underworld.h"
#include <QString>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QGraphicsRectItem>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QDebug>
#include <QTimer>
#include "gun.h"
GameView::GameView()
{
    //add scene
    scene = new QGraphicsScene(this);

    //add background
    scene->setSceneRect(0, 0, width(), height());
    QImage *img = new QImage(":/images/grass.png");
    *img = img->scaled(100,100,Qt::KeepAspectRatioByExpanding);
    QBrush bg_brush(*img);
    scene ->setBackgroundBrush(bg_brush);

    //add player
    QPixmap sprite = QPixmap(":/images/player.png");
    sprite = sprite.scaled(100,100,Qt::KeepAspectRatio);
    Bounds bound = {-20000, -20000, 20000, 20000};
    player *boy = new player(sprite, 5, 10, bound);
    boy->setFlag(QGraphicsItem::ItemIsFocusable,true);

    player_=boy;

    Gun *trash = new Gun();
    trash->setPos(100,100);
    scene->addItem(trash);

    scene->addItem(boy);
    boy->setFocus();

    connect(timer_, SIGNAL(timeout()), this, SLOT(SwitchToUnderWorld()));
    timer_->start(100);


    setScene(scene);
    setSceneRect(scene->sceneRect());
    setMinimumSize(1800, 1200);
}

void GameView::SwitchToUnderWorld() {
    timer_->stop();
    scene->clear();
    Bounds bound = {-20000, -20000, 20000, 20000};
    QPixmap enemy_sprite = QPixmap(":/images/Gr8.png");
    enemy_sprite = enemy_sprite.scaled(300, 300, Qt::KeepAspectRatio);
    Enemy *e = new Enemy(enemy_sprite, 5, 10, bound);
    Underworld * u = new Underworld(scene, e, player_);
}
