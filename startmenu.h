#ifndef STARTMENU_H
#define STARTMENU_H
#include <QWidget>

class StartMenu : public QWidget
{
    Q_OBJECT
public:
    StartMenu(QWidget *parent = 0);

public slots:
    void play_single_player();
    void play_two_player();
    void play_simulation();
};

#endif // STARTMENU_H
