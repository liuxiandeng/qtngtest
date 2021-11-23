#include "mainwindow.h"

#include <QtWidgets/qapplication.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return qtng::startQtLoop();
    //return a.exec();
}
