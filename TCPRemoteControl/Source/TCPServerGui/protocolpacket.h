#ifndef PROTOCOLPACKET_H
#define PROTOCOLPACKET_H

#include <QObject>
#include <QDataStream>

class ProtocolPacket : public QObject
{
    Q_OBJECT
public:
    enum COMMAND_TYPE
    {
        GET_VOLUME_MUTE = 100,
        SET_VOLUME_MUTE,
        GET_VOLUME_LEVEL,
        SET_VOLUME_LEVEL,
        STOP,
        PLAY,
        PAUSE,
        SET_SHUFFLE,
        GET_SHUFFLE,
        QUIT,
        NEXT_TRACK,
        PREV_TRACK,
        GET_STATE,
        GET_POSITION,
        SET_POSITION,
        GET_DURATION,
        LA_PLAY,
        LA_NEXT,
        LA_PREV,
        LA_FULLSCREEN,
        LA_NOT_FULLSCREEN,
        LA_LEFT,
        LA_RIGHT,
        PC_SHUTDOWN,
        AIMP_LAUNCH,
        UNKNOWN,
        GET_SYSTEM_VOLUME,
        SET_SYSTEM_VOLUME,
        SET_SYSTEM_MUTE,
        GET_SYSTEM_MUTE,
        PC_SLEEP
    };
    enum PLAY_STATE
    {
        STATE_STOP = 0, STATE_PAUSE, STATE_PLAY, STATE_UNKNOWN
    };

    ProtocolPacket(QObject *object = 0) : QObject(object)
    {
        command = UNKNOWN;
        value = 0;
    }

    ProtocolPacket(int _command, int _value, QObject *object = 0) : QObject(object)
    {
        command = _command;
        value = _value;
    }

    ProtocolPacket(const ProtocolPacket &other) : QObject(other.parent())
    {
        command = other.command;
        value = other.value;
    }

    friend QDataStream &operator<<(QDataStream &out, const ProtocolPacket &myObj)
    {
        out << myObj.command;
        out << myObj.value;
        return out;
    }

    friend QDataStream &operator>>(QDataStream &in, ProtocolPacket &myObj)
    {
        in >> myObj.command;
        in >> myObj.value;
        return in;
    }

    ProtocolPacket const & operator = (const ProtocolPacket & other)
    {
        command = other.command;
        value = other.value;
        return *this;
    }

public:
    int command;
    int value;
};

Q_DECLARE_METATYPE(ProtocolPacket)



#endif // PROTOCOLPACKET_H
