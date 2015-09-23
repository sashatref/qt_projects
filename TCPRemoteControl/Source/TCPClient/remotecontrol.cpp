#include "remotecontrol.h"

RemoteControl::RemoteControl(QObject *parent) :
    QObject(parent)
{
    m_pTcpSocket = new QTcpSocket(this);

    connect(m_pTcpSocket, SIGNAL(connected()), SIGNAL(connectedToHost()));
    connect(m_pTcpSocket, SIGNAL(disconnected()), SIGNAL(disconnectedFromHost()));
    connect(m_pTcpSocket, SIGNAL(readyRead()), SLOT(receiveMessageSlot()));
    connect(m_pTcpSocket,
            SIGNAL(error(QAbstractSocket::SocketError)),
            this,
            SLOT(connectionErrorSlot(QAbstractSocket::SocketError)));
}

void RemoteControl::connectToRemoteHost(const QString host, int port)
{
    m_pTcpSocket->connectToHost(host, port);

    sendMessage(ProtocolPacket::GET_DURATION, 1);
    sendMessage(ProtocolPacket::GET_POSITION, 1);
    sendMessage(ProtocolPacket::GET_STATE, 1);
    sendMessage(ProtocolPacket::GET_VOLUME_LEVEL, 1);
    sendMessage(ProtocolPacket::GET_SHUFFLE, 1);
    sendMessage(ProtocolPacket::GET_SYSTEM_MUTE, 1);
    sendMessage(ProtocolPacket::GET_SYSTEM_VOLUME, 1);
}

void RemoteControl::disconnectFromHost()
{
    m_pTcpSocket->close();
}

void RemoteControl::sendMessage(int command, int value)
{
    ProtocolPacket packet;
    packet.command = command;
    packet.value = value;

    QDataStream stream(m_pTcpSocket);
    stream.setVersion(QDataStream::Qt_5_4);
    stream << packet;
}

void RemoteControl::receiveMessageSlot()
{
    QDataStream stream(m_pTcpSocket);
    while(!stream.atEnd())
    {
        ProtocolPacket packet;
        stream >> packet;

        emit receiveMessage(packet);
    }
}

void RemoteControl::connectionErrorSlot(QAbstractSocket::SocketError err)
{
    QString strError =
        "Error: " + (err == QAbstractSocket::HostNotFoundError ?
                     "The host was not found." :
                     err == QAbstractSocket::RemoteHostClosedError ?
                     "The remote host is closed." :
                     err == QAbstractSocket::ConnectionRefusedError ?
                     "The connection was refused." :
                     QString(m_pTcpSocket->errorString())
                    );
    emit connectionError(strError);
}
