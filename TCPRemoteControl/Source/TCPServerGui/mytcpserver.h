#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>
#include "protocolpacket.h"
#include "winapifunctions.h"
#include <QFile>
#include <QTextBrowser>



class MyTCPServer : public QObject
{
    Q_OBJECT
public:
    MyTCPServer(int port = 44405, QTextBrowser *_log = 0,  QObject *object = 0);
    ~MyTCPServer();

    void setAimpPath(QString path);

signals:

    void clientConnected(QString text);

public slots:
    virtual void slotNewConnection();
    void slotReadClient();
    void clientDisconnected();

private:
    QTcpServer* m_ptcpServer;
    quint16     m_nNextBlockSize;

    void sendToClient(QTcpSocket* pSocket, const QString& str);
    void execMessage(ProtocolPacket packet);

    void log(QString text);

    QTextBrowser *m_log;
    QString m_aimpPath;
};

#endif // MYTCPSERVER_H
