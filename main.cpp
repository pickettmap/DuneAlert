#include "startmenu.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    StartMenu w;
    w.setMinimumSize(1920,1280);
    w.show();
    return a.exec();
}
