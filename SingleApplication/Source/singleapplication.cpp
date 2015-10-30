#include "singleapplication.h"
#include <QLocalSocket>
#include <QLocalServer>
#include <Windows.h>

class SingleApplicationPrivate
{
public:
    SingleApplicationPrivate(const QString &_uniqueName):
        m_server(0),
        m_uniqueName(_uniqueName),
        m_isRunning(false),
        m_mutex(0)
    {}

    ~SingleApplicationPrivate()
    {
        if(m_server) delete m_server;
    }

    bool m_isRunning;
    QString m_uniqueName;
    HANDLE m_mutex;
    QLocalServer *m_server;
};

SingleApplication::SingleApplication(int argc, char **argv, const QString &_uniqueName) :
    QApplication(argc, argv),
    m_private(new SingleApplicationPrivate(_uniqueName))
{
    m_private->m_mutex = CreateMutex(NULL, FALSE, (QString("Global\\") + _uniqueName + "_QtSingleApplicationMutex").toStdWString().c_str());
    if(GetLastError() == ERROR_ALREADY_EXISTS)
    {
        m_private->m_isRunning = true;
        {
            QLocalSocket socket;
            socket.connectToServer(m_private->m_uniqueName + "_QtLocalServer");
            socket.close();
        }
    } else
    {
        m_private->m_isRunning = false;
        m_private->m_server = new QLocalServer();
        m_private->m_server->listen(_uniqueName + "_QtLocalServer");
        connect(m_private->m_server, &QLocalServer::newConnection, this, &SingleApplication::onAnotherInstanceLaunch);
        m_private->m_server->waitForNewConnection();
    }
}

SingleApplication::~SingleApplication()
{
    if(!m_private->m_isRunning)
    {
       ReleaseMutex(m_private->m_mutex);
    }
    CloseHandle(m_private->m_mutex);

    delete m_private;
}

bool SingleApplication::isRunning()
{
    return m_private->m_isRunning;
}


