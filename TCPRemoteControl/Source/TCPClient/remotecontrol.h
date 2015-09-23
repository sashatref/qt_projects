#ifndef REMOTECONTROL_H
#define REMOTECONTROL_H

#include <QObject>
#include <QTcpSocket>
#include "../TCPServerGui/protocolpacket.h"

class RemoteControl : public QObject
{
    Q_OBJECT
public:
    explicit RemoteControl(QObject *parent = 0);
    void connectToRemoteHost(const QString host, int port = 44405);
    void disconnectFromHost();

signals:
    void connectedToHost();
    void disconnectedFromHost();
    void connectionError(QString error);
    void receiveMessage(ProtocolPacket);

public slots:
    void sendMessage(int command, int value);

private slots:
    void receiveMessageSlot();
    void connectionErrorSlot(QAbstractSocket::SocketError err);

private:
    QTcpSocket* m_pTcpSocket;
};



#endif // REMOTECONTROL_H
