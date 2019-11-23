#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QTimer>


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

    QGraphicsScene * scene;

public slots:
    void SwitchToUnderWorld();

private:
    GameView();
    QTimer *timer_ = new QTimer(this);
};

#endif // GAMEVIEW_H
