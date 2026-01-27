/** Made by I'Pancake **/

//#include "choose_your_fate.h"
#include <QApplication>
#include "mainwindow.h"
//#include <exception>
//#include <iostream>

int main(int argc, char **argv)
{
    QApplication *p = new QApplication(argc, argv);

    MainWindow *m = new MainWindow();

    m->show();
    return p->exec();
}
