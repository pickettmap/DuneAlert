#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QTimer>
#include "player.h"


class GameView : public QGraphicsView
{
    Q_OBJECT
public:
    static GameView& GetInstance() {
        static GameView instance;
        return instance;
    }

    GameView(GameView const&) = delete;
    void operator=(GameView const&) = delete;

    player* get_player(){return player_;}
    void CreateOverworld();

    QGraphicsScene * scene;

    void keyPressEvent(QKeyEvent * event);
    void keyReleaseEvent(QKeyEvent *event);


public slots:
    void SwitchToUnderWorld();

signals:
    void onPOneKeyPressed(QKeyEvent * event);
    void onPTwoKeyPressed(QKeyEvent * event);
    void onKeyPressed(QKeyEvent * event);
    void onKeyRelease(QKeyEvent * event);

private:
    GameView();
    QTimer *timer_ = new QTimer(this);
    player *player_;
};

#endif // GAMEVIEW_H
