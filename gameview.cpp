#include "gameview.h"
#include "player.h"
#include "underworld.h"
#include <QString>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QGraphicsRectItem>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QDebug>

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
    player *boy = new player(sprite);
    boy->setFlag(QGraphicsItem::ItemIsFocusable,true);
    boy->setFocus();

    scene->addItem(boy);

    QPushButton *play_btn = new QPushButton("Switch To Underworld", this);
    scene->addWidget(play_btn);

    connect(play_btn,SIGNAL(clicked()),this,SLOT(SwitchToUnderWorld()));

    setScene(scene);
    setSceneRect(scene->sceneRect());

    setMinimumSize(1000,800);
}

void GameView::SwitchToUnderWorld() {
    scene->clear();
    //This is a placeholder for future code as a proof of concept
    Underworld * u = new Underworld(scene);
}
