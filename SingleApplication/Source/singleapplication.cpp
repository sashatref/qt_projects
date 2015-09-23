#include "singleapplication.h"
#include <QLocalSocket>

SingleApplication::SingleApplication(int argc, char **argv, QString _uniqueName) :
    QApplication(argc, argv),
    m_server(0),
    m_uniqueName(_uniqueName)
{
    m_mutex = CreateMutex(NULL, FALSE, (QString("Global\\") + _uniqueName + "_QtSingleApplicationMutex").toStdWString().c_str());
    if(GetLastError() == ERROR_ALREADY_EXISTS)
    {
        m_isRunning = true;
        sendAppWake();
    } else
    {
        m_isRunning = false;
        m_server = new QLocalServer();
        m_server->listen(_uniqueName + "_QtLocalServer");
        connect(m_server, SIGNAL(newConnection()), this, SIGNAL(onAnotherInstanceLaunch()));
        m_server->waitForNewConnection();
    }
}

SingleApplication::~SingleApplication()
{
    if(!m_isRunning)
    {
       ReleaseMutex(m_mutex);
    }
    CloseHandle(m_mutex);

    if(m_server) delete m_server;
}

void SingleApplication::sendAppWake()
{
    QLocalSocket socket;
    socket.connectToServer(m_uniqueName + "_QtLocalServer");
    socket.close();
}


