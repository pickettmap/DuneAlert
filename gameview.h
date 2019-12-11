#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QTimer>
#include "player.h"
#include "item.h"
#include "secondplayer.h"
#include "enemy.h"
#include "computerplayer.h"

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
    void CreateBackGround();

    void RemovePlayer();

    void EndGame();

    void makeToilets(int arr[2]);

    QGraphicsScene * scene;

    void keyPressEvent(QKeyEvent * event);
    void keyReleaseEvent(QKeyEvent *event);

    void SetMode(Mode mode) { mode_ = mode; }

    void determineAIFightSequence();


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
    bool in_overworld_;
private:
    GameView();
    player * player_;
    SecondPlayer * player2_;
    int player_one_position_ [2];
    int player_two_position_ [2];
    int ai_position_ [2];
    ComputerPlayer * ai;
    Mode mode_;
};

#endif // GAMEVIEW_H
