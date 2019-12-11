#ifndef STARTMENU_H
#define STARTMENU_H
#include <QWidget>
#include <QGraphicsScene>
#include <QLabel>
#include "finalgraph.h"

class StartMenu : public QWidget
{
    Q_OBJECT
public:
    StartMenu(QWidget *parent = 0);

public slots:
    void play_single_player();
    void play_two_player();
    void play_simulation();
    void UpdateGraph(int);

private:
    FinalGraph * wins_;
    FinalGraph * loses_;
    QGraphicsScene * scene_;
    float win_count_ = 0;
    float loss_count_ = 0;
    QLabel * l;

};

#endif // STARTMENU_H
