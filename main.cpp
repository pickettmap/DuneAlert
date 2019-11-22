#include "startmenu.h"
#include "gameview.h"

#include <stdlib.h>
#include <time.h>
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    StartMenu w;
    srand(time(0));
    w.setMinimumSize(800,800);
    w.show();
    return a.exec();
}
