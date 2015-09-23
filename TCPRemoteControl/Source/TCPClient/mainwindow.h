#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "remotecontrol.h"
#include <QProcess>
#include <QSettings>
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    RemoteControl *remoteControl;

public slots:
    void connected();
    void disconnected();
private slots:
    void on_prevButton_clicked();
    void on_stopButton_clicked();
    void on_playButton_clicked();
    void on_nextButton_clicked();
    void on_pauseButton_clicked();
    void on_muteButton_clicked();
    void on_connectButton_clicked();
    void on_disconnectButtob_clicked();

    void receiveMessage(ProtocolPacket packet);
    void on_laLEft_clicked();
    void on_laRight_clicked();
    void on_laFullScreen_clicked();
    void on_laNotFull_clicked();
    void on_laPlayButton_clicked();
    void on_laPrevButton_clicked();
    void on_laNextButton_clicked();
    void on_minusVolumeButton_clicked();
    void on_plusVolumeButton_clicked();
    void on_shutdownPcButton_clicked();
    void on_shuffleButton_clicked();
    void on_closeAimpButton_clicked();
    void on_launchAimpButton_clicked();
    void on_sleepButton_clicked();
    void on_systemVolumeMuteButton_clicked();
    void on_systemVolumeMinusButton_clicked();
    void on_systemVolumePlusButton_clicked();
};

#endif // MAINWINDOW_H
