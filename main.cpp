/** Made by I'Pancake **/

//#include "choose_your_fate.h"
#include "mainwindow.h"
#include "qapplication.h"
#include <exception>
#include <iostream>

int main(int argc, char **argv)
{
    QApplication *p = new QApplication(argc, argv);
    //    try {
    //        choose_your_fate(argc, argv);

    //    } catch (std::exception &e) {
    //        std::cerr << e.what() << std::endl;
    //    }

    MainWindow *m = new MainWindow();
    m->show();
    return p->exec();
}
