#include "mytcpserver.h"
#include <QDateTime>

MyTCPServer::MyTCPServer(int port, QTextBrowser *_log, QObject *object) :
    QObject(object)
{
    m_log = _log;
    m_ptcpServer = new QTcpServer(this);
    if (!m_ptcpServer->listen(QHostAddress::Any, port)) {
        qDebug() <<  "Unable to start the server:" + m_ptcpServer->errorString();
        m_ptcpServer->close();
        return;
    }

    connect(m_ptcpServer, SIGNAL(newConnection()), this, SLOT(slotNewConnection()));

    log("Server started\nWaiting for clients...");
}

MyTCPServer::~MyTCPServer()
{

}

void MyTCPServer::setAimpPath(QString path)
{
    m_aimpPath = path;
}

void MyTCPServer::slotNewConnection()
{
    QTcpSocket* pClientSocket = m_ptcpServer->nextPendingConnection();
    connect(pClientSocket, SIGNAL(disconnected()), pClientSocket, SLOT(deleteLater()));
    connect(pClientSocket, SIGNAL(disconnected()), this, SLOT(clientDisconnected()));
    connect(pClientSocket, SIGNAL(readyRead()), this, SLOT(slotReadClient()));

    log("Client connected from: " + pClientSocket->peerAddress().toString());
    emit clientConnected("Client connected from: " + pClientSocket->peerAddress().toString());
}

void MyTCPServer::slotReadClient()
{
    QTcpSocket* pClientSocket = (QTcpSocket*)sender();
    QDataStream in(pClientSocket);
    in.setVersion(QDataStream::Qt_5_4);

    while (!in.atEnd()) {
        ProtocolPacket packet;
        in >> packet;

        //log("Receive: " + QString::number(packet.command) + "\n");

        switch(packet.command)
        {
        case ProtocolPacket::LA_LEFT:
        {
            log("Click la left");
            LA::clickLALeft();
            break;
        }
        case ProtocolPacket::LA_RIGHT:
        {
            log("Click la right");
            LA::clickLARight();
            break;
        }
        case ProtocolPacket::LA_FULLSCREEN:
        {
            log("Click la fullscreen");
            LA::clickLAFullScreen();
            break;
        }
        case ProtocolPacket::LA_NEXT:
        {
            log("Click la next");
            LA::clickLANext();
            break;
        }
        case ProtocolPacket::LA_PLAY:
        {
            log("Click la play");
            LA::clickLAPlay();
            break;
        }
        case ProtocolPacket::LA_PREV:
        {
            log("Click la prev");
            LA::clickLAPrev();
            break;
        }
        case ProtocolPacket::SET_VOLUME_MUTE:
        {
            log("Set volume Mute " + QString::number(packet.value));
            Aimp::setMuteStatus(packet.value);
            in << ProtocolPacket(ProtocolPacket::SET_VOLUME_MUTE, packet.value);
            break;
        }
        case ProtocolPacket::SET_POSITION:
        {
            log("Set position " + QString::number(packet.value));
            Aimp::setPosition(packet.value);
            in << ProtocolPacket(ProtocolPacket::SET_POSITION, packet.value);
            break;
        }
        case ProtocolPacket::SET_SHUFFLE:
        {
            log("Set shuffle " + QString::number(packet.value));
            Aimp::setShuffle(packet.value);
            in << ProtocolPacket(ProtocolPacket::SET_SHUFFLE, packet.value);
            break;
        }
        case ProtocolPacket::SET_VOLUME_LEVEL:
        {
            if(packet.value > 100) packet.value = 100;
            else if(packet.value < 0) packet.value = 0;

            log("Set volume level " + QString::number(packet.value));
            Aimp::setVolumeLevel(packet.value);
            in << ProtocolPacket(ProtocolPacket::SET_VOLUME_LEVEL, packet.value);
            break;
        }
        case ProtocolPacket::PC_SHUTDOWN:
        {
            log("Set pc shutdown " + QString::number(packet.value));
            System::pc_shutdown();
            break;
        }
        case ProtocolPacket::NEXT_TRACK:
        {
            log("Set next track " + QString::number(packet.value));
            Aimp::nextTrack();
            break;
        }
        case ProtocolPacket::PREV_TRACK:
        {
            log("Set prev track " + QString::number(packet.value));
            Aimp::prevTrack();
            break;
        }
        case ProtocolPacket::PLAY:
        {
            log("Set play " + QString::number(packet.value));
            Aimp::play();
            break;
        }
        case ProtocolPacket::STOP:
        {
            log("Set stop " + QString::number(packet.value));
            Aimp::stop();
            break;
        }
        case ProtocolPacket::PAUSE:
        {
            log("Set pause " + QString::number(packet.value));
            Aimp::pause();
            break;
        }
        case ProtocolPacket::QUIT:
        {
            log("Set quit " + QString::number(packet.value));
            Aimp::quit();
            break;
        }
        case ProtocolPacket::AIMP_LAUNCH:
        {
            log("Aimp launch " + QString::number(packet.value));
            Aimp::aimp_launch(m_aimpPath);
            break;
        }
        case ProtocolPacket::GET_VOLUME_MUTE:
        {
            int res = Aimp::getMuteStatus();
            log("Get volume Mute " + QString::number(res));
            in << ProtocolPacket(ProtocolPacket::GET_VOLUME_MUTE, res);
            break;
        }
        case ProtocolPacket::GET_VOLUME_LEVEL:
        {
            int res = Aimp::getVolumeLevel();
            log("Get volume level " + QString::number(res));
            in << ProtocolPacket(ProtocolPacket::GET_VOLUME_LEVEL, res);
            break;
        }
        case ProtocolPacket::GET_SHUFFLE:
        {
            int res = Aimp::getShuffle();
            log("Get shuffle " + QString::number(res));
            in << ProtocolPacket(ProtocolPacket::GET_SHUFFLE, res);
            break;
        }
        case ProtocolPacket::GET_DURATION:
        {
            int res = Aimp::getDuration();
            log("Get duration: " + QString::number(res));
            in << ProtocolPacket(ProtocolPacket::GET_DURATION, res);
            break;
        }
        case ProtocolPacket::GET_POSITION:
        {
            int res = Aimp::getPosition();
            log("Get position: " + QString::number(res));
            in << ProtocolPacket(ProtocolPacket::GET_POSITION, res);
            break;
        }
        case ProtocolPacket::GET_STATE:
        {
            int res = Aimp::getState();
            log("Get state: " + QString::number(res));
            in << ProtocolPacket(ProtocolPacket::GET_STATE, res);
            break;
        }
        case ProtocolPacket::PC_SLEEP:
        {
            log("Set pc shutdown " + QString::number(packet.value));
            System::pc_sleep();
            break;
        }
        case ProtocolPacket::SET_SYSTEM_VOLUME:
        {
            if(packet.value > 100) packet.value = 100;
            else if(packet.value < 0) packet.value = 0;

            log("Set system volume level " + QString::number(packet.value));

            System::setVolumeLevel(packet.value);
            in << ProtocolPacket(ProtocolPacket::SET_SYSTEM_VOLUME, packet.value);
            break;
        }
        case ProtocolPacket::GET_SYSTEM_VOLUME:
        {
            int res = System::getVolumeLevel();
            log("Get system volume Mute " + QString::number(res));
            in << ProtocolPacket(ProtocolPacket::GET_SYSTEM_VOLUME, res);
            break;
        }
        case ProtocolPacket::GET_SYSTEM_MUTE:
        {
            int res = System::getMuteStatus();
            log("Get system volume Mute " + QString::number(res));
            in << ProtocolPacket(ProtocolPacket::GET_SYSTEM_MUTE, res);
            break;
        }
        case ProtocolPacket::SET_SYSTEM_MUTE:
        {
            System::volume_mute(packet.value);
            log("Get system volume Mute " + QString::number(packet.value));
            in << ProtocolPacket(ProtocolPacket::SET_SYSTEM_MUTE, packet.value);
            break;
        }
        }
    }
}

void MyTCPServer::sendToClient(QTcpSocket *pSocket, const QString&)
{
    QDataStream out(pSocket);
    out.setVersion(QDataStream::Qt_5_4);

    ProtocolPacket packet;
    out >> packet;

    //log("Receive: " + QString::number(packet.command) + "\n");
}

void MyTCPServer::log(QString text)
{
    if(m_log)
    {
        m_log->append(QDateTime::currentDateTime().toString("hh:mm:ss") + " | " + text);
    } else
    {
        qDebug() << "LogBrowser is 0";
    }
}

void MyTCPServer::clientDisconnected()
{
    log("Client disconnected!");
}

