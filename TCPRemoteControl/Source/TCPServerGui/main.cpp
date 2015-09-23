#include "mainwindow.h"
#include <QApplication>
#include "singleapplication.h"

int main(int argc, char *argv[])
{
    SingleApplication app(argc, argv, "TcpServerRemoteControl");

    if (app.isRunning())
    {
        return 0;
    }

    MainWindow mmw;
    QObject::connect(&app, SIGNAL(onAnotherInstanceLaunch()),
                     &mmw, SLOT(receiveMessage()));
    mmw.show();

    if(argc == 2 && QString(argv[1]) == "-hidden")
    {
       mmw.hideOnStartUp();
    }

    return app.exec();
}
