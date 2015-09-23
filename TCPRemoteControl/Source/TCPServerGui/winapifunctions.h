#ifndef WINAPIFUNCTIONS_H
#define WINAPIFUNCTIONS_H

#define NOMINMAX
#include <Windows.h>
#include <QString>
#include <QProcess>

class Aimp
{
public:
    static HWND getAimpWindow();
    static int getMuteStatus();
    static void setMuteStatus(int isEnable);
    static int getVolumeLevel();
    static void setVolumeLevel(int volumeLevel);
    static void aimp_launch(QString path);
    static void setShuffle(bool isEnable);
    static int getShuffle();
    static int getState();
    static void quit();
    static void nextTrack();
    static void prevTrack();
    static void pause();
    static void stop();
    static void play();
    static int getPosition();
    static void setPosition(int position);
    static int getDuration();
    static int getAlbumArt();
};

class LA
{
public:
    static void clickLAPlay();
    static void clickLAFullScreen();
    static void clickLANext();
    static void clickLAPrev();
    static void clickLALeft();
    static void clickLARight();
    static HWND getLAWindow();
};

class System
{
public:
    static void pc_shutdown();
    static void pc_sleep();
    static void volume_mute(bool _isEnable);
    static void setVolumeLevel(int _value);
    static int getVolumeLevel();
    static int getMuteStatus();
};


const int WM_AIMP_PROPERTY = WM_USER + 0x77;
const int WM_AIMP_COMMAND = WM_USER + 0x75;

const int AIMP_RA_PROPERTY_MUTE = 0x60;
const int AIMP_RA_PROPVALUE_SET = 1;
const int AIMP_RA_PROPVALUE_GET = 0;

const int AIMP_RA_PROPERTY_PLAYER_POSITION = 0x20;
const int AIMP_RA_PROPERTY_PLAYER_DURATION = 0x30;

const int AIMP_RA_CMD_BASE = 10;
const int AIMP_RA_CMD_REGISTER_NOTIFY = AIMP_RA_CMD_BASE + 1;
const int AIMP_RA_CMD_UNREGISTER_NOTIFY = AIMP_RA_CMD_BASE + 2;
const int AIMP_RA_CMD_PLAY = AIMP_RA_CMD_BASE + 3;
const int AIMP_RA_CMD_PLAYPAUSE = AIMP_RA_CMD_BASE + 4;
const int AIMP_RA_CMD_PAUSE = AIMP_RA_CMD_BASE + 5;
const int AIMP_RA_CMD_STOP = AIMP_RA_CMD_BASE + 6;
const int AIMP_RA_CMD_NEXT = AIMP_RA_CMD_BASE + 7;
const int AIMP_RA_CMD_PREV = AIMP_RA_CMD_BASE + 8;
const int AIMP_RA_CMD_VISUAL_NEXT = AIMP_RA_CMD_BASE + 9;
const int AIMP_RA_CMD_VISUAL_PREV = AIMP_RA_CMD_BASE + 10;
const int AIMP_RA_CMD_QUIT = AIMP_RA_CMD_BASE + 11;
const int AIMP_RA_CMD_ADD_FILES = AIMP_RA_CMD_BASE + 12;
const int AIMP_RA_CMD_ADD_FOLDERS = AIMP_RA_CMD_BASE + 13;
const int AIMP_RA_CMD_ADD_PLAYLISTS = AIMP_RA_CMD_BASE + 14;
const int AIMP_RA_CMD_ADD_URL = AIMP_RA_CMD_BASE + 15;
const int AIMP_RA_CMD_OPEN_FILES = AIMP_RA_CMD_BASE + 16;
const int AIMP_RA_CMD_OPEN_FOLDERS = AIMP_RA_CMD_BASE + 17;
const int AIMP_RA_CMD_OPEN_PLAYLISTS = AIMP_RA_CMD_BASE + 18;

const int AIMP_RA_PROPERTY_TRACK_SHUFFLE = 0x80;
const int AIMP_RA_PROPERTY_VOLUME = 0x50;

const int AIMP_RA_NOTIFY_BASE = 0;
const int AIMP_RA_NOTIFY_TRACK_INFO = AIMP_RA_NOTIFY_BASE + 1;
const int AIMP_RA_NOTIFY_TRACK_START = AIMP_RA_NOTIFY_BASE + 2;
const int AIMP_RA_NOTIFY_PROPERTY = AIMP_RA_NOTIFY_BASE + 3;

const int AIMP_RA_PROPERTY_PLAYER_STATE = 0x40;

#endif // WINAPIFUNCTIONS_H
