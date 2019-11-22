#ifndef STARTMENU_H
#define STARTMENU_H
#include <QWidget>

class StartMenu : public QWidget
{
    Q_OBJECT
public:
    StartMenu(QWidget *parent = 0);

public slots:
    void play();
};

#endif // STARTMENU_H
