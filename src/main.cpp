/** Made by I'm Pancake **/

//#include "choose_your_fate.h"
#include <QApplication>
#include "gui/mainwindow.h"
//#include <exception>
//#include <iostream>

int main(int argc, char **argv)
{
    QApplication p(argc, argv);

    MainWindow m;
    m.show();

    return p.exec();
}
