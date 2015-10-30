#pragma once

#include <QApplication>

class SingleApplicationPrivate;
class SingleApplication : public QApplication
{
    Q_OBJECT
public:
    SingleApplication(int argc, char** argv, const QString &_uniqueName);
    ~SingleApplication();

    bool isRunning();

signals:
    void onAnotherInstanceLaunch();

private:
    SingleApplicationPrivate *m_private;
};
