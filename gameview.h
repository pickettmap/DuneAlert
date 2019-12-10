#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QTimer>
#include "player.h"
#include "item.h"
#include "secondplayer.h"
#include "enemy.h"

enum Mode {SinglePlayer, TwoPlayer, Simulation};

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
    Mode get_game_mode(){ return mode_; }

    void CreateSinglePlayerOverWorld();
    void CreateTwoPlayerOverWorld();
    void CreateAIOverworld();
//    void CreateOverworld();

    QGraphicsScene * scene;

    void keyPressEvent(QKeyEvent * event);
    void keyReleaseEvent(QKeyEvent *event);

    void SetMode(Mode mode) { mode_ = mode; }


public slots:
    void SwitchToUnderWorld(player *p, Enemy *e);

signals:
    void onPOneKeyPressed(QKeyEvent * event);
    void onPTwoKeyPressed(QKeyEvent * event);
    void onKeyPressed(QKeyEvent * event);
    void onKeyRelease(QKeyEvent * event);


public:
    bool switching_to_underworld_;
    bool switching_to_overworld_;
private:
    GameView();
    player * player_;
    SecondPlayer * player2_;
    std::vector<int> player_one_position_;
    std::vector<int> player_two_position_;
    Mode mode_;
};

#endif // GAMEVIEW_H
