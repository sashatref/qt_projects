#include "mainwindow.h"
#include <QApplication>
#include "singleapplication.h"

int main(int argc, char *argv[])
{
    SingleApplication a(argc, argv, "myProgramm");
    if(a.isRunning()) { return 0;}

    MainWindow w;
    QObject::connect(&a, &SingleApplication::onAnotherInstanceLaunch, &w, &MainWindow::anotherAppInstanceLaunch);
    w.show();

    return a.exec();
}
