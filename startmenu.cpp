#include "startmenu.h"
#include <QString>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

StartMenu::StartMenu(QWidget *parent)
{
    QLabel *title = new QLabel("DUNEALERT",this);
    title->setAlignment(Qt::AlignHCenter);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(title);

    setLayout(layout);
}
