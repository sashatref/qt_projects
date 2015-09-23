#include "winapifunctions.h"
#include <endpointvolume.h>
#include <mmdeviceapi.h>
#include <stdio.h>
#include <QFile>

HWND Aimp::getAimpWindow()
{
    return FindWindow(NULL, QString("AIMP2_RemoteInfo").toStdWString().c_str());

}

HWND LA::getLAWindow()
{
    return FindWindow(QString("LightAlloyFront").toStdWString().c_str(), NULL);
}

int Aimp::getMuteStatus()
{
    HWND parentWindow = getAimpWindow();
    if(parentWindow)
    {
        return SendMessage(parentWindow, WM_AIMP_PROPERTY, (AIMP_RA_PROPERTY_MUTE | AIMP_RA_PROPVALUE_GET), 0);
    }
    return -1;
}

void Aimp::setMuteStatus(int isEnable)
{
    HWND parentWindow = getAimpWindow();
    if(parentWindow)
        SendMessage(parentWindow, WM_AIMP_PROPERTY, (AIMP_RA_PROPERTY_MUTE | AIMP_RA_PROPVALUE_SET), isEnable);
}

int Aimp::getVolumeLevel()
{
    HWND parentWindow = getAimpWindow();
    LRESULT result = SendMessage(parentWindow, WM_AIMP_PROPERTY, (AIMP_RA_PROPERTY_VOLUME | AIMP_RA_PROPVALUE_GET), 0);
    return result;
}

void Aimp::setVolumeLevel(int volumeLevel)
{
    HWND parentWindow = getAimpWindow();
    if(parentWindow)
        SendMessage(parentWindow, WM_AIMP_PROPERTY, (AIMP_RA_PROPERTY_VOLUME | AIMP_RA_PROPVALUE_SET), volumeLevel);
}

void Aimp::nextTrack()
{
    HWND parentWindow = getAimpWindow();
    if(parentWindow)
        SendMessage(parentWindow, WM_AIMP_COMMAND, AIMP_RA_CMD_NEXT, 0);
}

void Aimp::prevTrack()
{
    HWND parentWindow = getAimpWindow();
    if(parentWindow)
        SendMessage(parentWindow, WM_AIMP_COMMAND, AIMP_RA_CMD_PREV, 0);
}

void Aimp::pause()
{
    HWND parentWindow = getAimpWindow();
    if(parentWindow)
        SendMessage(parentWindow, WM_AIMP_COMMAND, AIMP_RA_CMD_PLAYPAUSE, 0);
}

void Aimp::stop()
{
    HWND parentWindow = getAimpWindow();
    if(parentWindow)
        SendMessage(parentWindow, WM_AIMP_COMMAND, AIMP_RA_CMD_STOP, 0);
}

void Aimp::play()
{
    HWND parentWindow = getAimpWindow();
    if(parentWindow)
        SendMessage(parentWindow, WM_AIMP_COMMAND, AIMP_RA_CMD_PLAY, 0);
}

void Aimp::quit()
{
    HWND parentWindow = getAimpWindow();
    if(parentWindow)
        SendMessage(parentWindow, WM_AIMP_COMMAND, AIMP_RA_CMD_QUIT, 0);
}

void Aimp::aimp_launch(QString path)
{
    if(QFile(path).exists())
    {
        QProcess::startDetached(path, QStringList());
    }
}

void Aimp::setShuffle(bool isEnable)
{
    HWND parentWindow = getAimpWindow();
    if(parentWindow)
        SendMessage(parentWindow, WM_AIMP_PROPERTY, AIMP_RA_PROPERTY_TRACK_SHUFFLE | AIMP_RA_PROPVALUE_SET, isEnable);
}

int Aimp::getShuffle()
{
    HWND parentWindow = getAimpWindow();
    if(parentWindow)
        return SendMessage(parentWindow, WM_AIMP_PROPERTY, AIMP_RA_PROPERTY_TRACK_SHUFFLE | AIMP_RA_PROPVALUE_GET, 0);
    return -1;
}

int Aimp::getState()
{
    HWND parentWindow = getAimpWindow();
    if(parentWindow)
        return SendMessage(parentWindow, WM_AIMP_PROPERTY, AIMP_RA_PROPERTY_PLAYER_STATE | AIMP_RA_PROPVALUE_GET, 0);
    return -1;
}

int Aimp::getPosition()
{
    HWND parentWindow = getAimpWindow();
    if(parentWindow)
        return SendMessage(parentWindow, WM_AIMP_PROPERTY, AIMP_RA_PROPERTY_PLAYER_POSITION | AIMP_RA_PROPVALUE_GET, 0) / 1000;
    return -1;
}

void Aimp::setPosition(int position)
{
    HWND parentWindow = getAimpWindow();
    if(parentWindow)
        SendMessage(parentWindow, WM_AIMP_PROPERTY, AIMP_RA_PROPERTY_PLAYER_POSITION | AIMP_RA_PROPVALUE_SET, position * 1000);
}

int Aimp::getDuration()
{
    HWND parentWindow = getAimpWindow();
    if(parentWindow)
        return SendMessage(parentWindow, WM_AIMP_PROPERTY, AIMP_RA_PROPERTY_PLAYER_DURATION | AIMP_RA_PROPVALUE_GET, 0) / 1000;
    return -1;
}

int Aimp::getAlbumArt()
{
    return 1;
}

void LA::clickLAPlay()
{
    HWND parentWindow = getLAWindow();
    SendMessage(parentWindow, WM_KEYDOWN, VK_SPACE, 0);
    SendMessage(parentWindow, WM_KEYUP, VK_SPACE, 0);
}

void LA::clickLAFullScreen()
{
    HWND parentWindow = getLAWindow();
    SendMessage(parentWindow, WM_KEYDOWN, VK_RETURN, 0);
    SendMessage(parentWindow, WM_KEYUP, VK_RETURN, 0);
}

void LA::clickLANext()
{
    HWND parentWindow = getLAWindow();
    SendMessage(parentWindow, WM_KEYDOWN, VK_NEXT, 0);
    SendMessage(parentWindow, WM_KEYUP, VK_NEXT, 0);
}

void LA::clickLAPrev()
{
    HWND parentWindow = getLAWindow();
    SendMessage(parentWindow, WM_KEYDOWN, VK_PRIOR, 0);
    SendMessage(parentWindow, WM_KEYUP, VK_PRIOR, 0);
}

void LA::clickLALeft()
{
    HWND parentWindow = getLAWindow();
    SendMessage(parentWindow, WM_KEYDOWN, VK_LEFT, 0);
    SendMessage(parentWindow, WM_KEYUP, VK_LEFT, 0);
}

void LA::clickLARight()
{
    HWND parentWindow = getLAWindow();
    SendMessage(parentWindow, WM_KEYDOWN, VK_RIGHT, 0);
    SendMessage(parentWindow, WM_KEYUP, VK_RIGHT, 0);
}

void System::pc_shutdown()
{
    QProcess::startDetached("shutdown.exe", QStringList() << "/s" << "/f" << "/t" << "3");
}

void System::pc_sleep()
{
    QProcess::startDetached("Rundll32.exe", QStringList() << "powrprof.dll,SetSuspendState" << "Sleep");
}

void System::volume_mute(bool _isEnable)
{
    CoInitialize(NULL);
    IMMDeviceEnumerator *deviceEnumerator = NULL;
    HRESULT hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_INPROC_SERVER, __uuidof(IMMDeviceEnumerator), (LPVOID *)&deviceEnumerator);
    IMMDevice *defaultDevice = NULL;

    hr = deviceEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &defaultDevice);
    deviceEnumerator->Release();
    deviceEnumerator = NULL;

    IAudioEndpointVolume *endpointVolume = NULL;
    hr = defaultDevice->Activate(__uuidof(IAudioEndpointVolume), CLSCTX_INPROC_SERVER, NULL, (LPVOID *)&endpointVolume);
    defaultDevice->Release();
    defaultDevice = NULL;

    endpointVolume->SetMute(_isEnable, NULL);

    endpointVolume->Release();

    CoUninitialize();
}

void System::setVolumeLevel(int _value)
{
    CoInitialize(NULL);
    IMMDeviceEnumerator *deviceEnumerator = NULL;
    HRESULT hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_INPROC_SERVER, __uuidof(IMMDeviceEnumerator), (LPVOID *)&deviceEnumerator);
    IMMDevice *defaultDevice = NULL;

    hr = deviceEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &defaultDevice);
    deviceEnumerator->Release();
    deviceEnumerator = NULL;

    IAudioEndpointVolume *endpointVolume = NULL;
    hr = defaultDevice->Activate(__uuidof(IAudioEndpointVolume), CLSCTX_INPROC_SERVER, NULL, (LPVOID *)&endpointVolume);
    defaultDevice->Release();
    defaultDevice = NULL;

    hr = endpointVolume->SetMasterVolumeLevelScalar((float)_value / 100, NULL);

    endpointVolume->Release();

    CoUninitialize();
}

int System::getVolumeLevel()
{
    CoInitialize(NULL);
    IMMDeviceEnumerator *deviceEnumerator = NULL;
    HRESULT hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_INPROC_SERVER, __uuidof(IMMDeviceEnumerator), (LPVOID *)&deviceEnumerator);
    IMMDevice *defaultDevice = NULL;

    hr = deviceEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &defaultDevice);
    deviceEnumerator->Release();
    deviceEnumerator = NULL;

    IAudioEndpointVolume *endpointVolume = NULL;
    hr = defaultDevice->Activate(__uuidof(IAudioEndpointVolume), CLSCTX_INPROC_SERVER, NULL, (LPVOID *)&endpointVolume);
    defaultDevice->Release();
    defaultDevice = NULL;

    float currentVolume;

    hr = endpointVolume->GetMasterVolumeLevelScalar(&currentVolume);

    endpointVolume->Release();

    CoUninitialize();

    return currentVolume * 100;
}

int System::getMuteStatus()
{
    CoInitialize(NULL);
    IMMDeviceEnumerator *deviceEnumerator = NULL;
    HRESULT hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_INPROC_SERVER, __uuidof(IMMDeviceEnumerator), (LPVOID *)&deviceEnumerator);
    IMMDevice *defaultDevice = NULL;

    hr = deviceEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &defaultDevice);
    deviceEnumerator->Release();
    deviceEnumerator = NULL;

    IAudioEndpointVolume *endpointVolume = NULL;
    hr = defaultDevice->Activate(__uuidof(IAudioEndpointVolume), CLSCTX_INPROC_SERVER, NULL, (LPVOID *)&endpointVolume);
    defaultDevice->Release();
    defaultDevice = NULL;

    BOOL muteStatus;

    hr = endpointVolume->GetMute(&muteStatus);

    endpointVolume->Release();

    CoUninitialize();

    return muteStatus;
}

