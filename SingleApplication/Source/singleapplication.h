#pragma once

#include <QApplication>
#include <QLocalServer>
#include <Windows.h>

class SingleApplication : public QApplication
{
    Q_OBJECT
public:
    SingleApplication(int argc, char** argv, QString _uniqueName);
    ~SingleApplication();

    bool isRunning() {return m_isRunning;}

signals:
    void onAnotherInstanceLaunch();

private:
    bool m_isRunning;
    QString m_uniqueName;
    HANDLE m_mutex;
    QLocalServer *m_server;

    void sendAppWake();
};
