#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QSettings conf("config.ini", QSettings::IniFormat);
    ui->adressLineEdit->setText(conf.value("lastIP", "127.0.0.1").toString());

    //ui->playButton->setIcon(QIcon("://Images/play.png"));
//    ui->playButton->setIconSize(ui->playButton->size());
//    ui->stopButton->setIconSize(ui->stopButton->size());
//    ui->prevButton->setIconSize(ui->prevButton->size());
//    ui->nextButton->setIconSize(ui->nextButton->size());
//    ui->pauseButton->setIconSize(ui->pauseButton->size());
//    ui->muteButton->setIconSize(ui->muteButton->size());


    remoteControl = new RemoteControl();
    connect(remoteControl, SIGNAL(connectedToHost()), this, SLOT(connected()));
    connect(remoteControl, SIGNAL(disconnectedFromHost()), this, SLOT(disconnected()));
    connect(remoteControl, SIGNAL(receiveMessage(ProtocolPacket)), this, SLOT(receiveMessage(ProtocolPacket)));
}

MainWindow::~MainWindow()
{
    QSettings conf("config.ini", QSettings::IniFormat);
    conf.setValue("lastIP", ui->adressLineEdit->text());
    delete ui;
    delete remoteControl;
}

void MainWindow::connected()
{
    ui->logTextBrowser->append("Connected to remote host");
    ui->pcTab->setEnabled(true);
    ui->aimpTab->setEnabled(true);
    ui->laTab->setEnabled(true);
}

void MainWindow::disconnected()
{
    ui->logTextBrowser->append("Disconnected from remote host");
    ui->pcTab->setEnabled(false);
    ui->aimpTab->setEnabled(false);
    ui->laTab->setEnabled(false);
}

void MainWindow::on_prevButton_clicked()
{
    remoteControl->sendMessage(ProtocolPacket::PREV_TRACK, 0);
}

void MainWindow::on_stopButton_clicked()
{
    remoteControl->sendMessage(ProtocolPacket::STOP, 0);
}

void MainWindow::on_playButton_clicked()
{
    remoteControl->sendMessage(ProtocolPacket::PLAY, 0);
}

void MainWindow::on_nextButton_clicked()
{
    remoteControl->sendMessage(ProtocolPacket::NEXT_TRACK, 0);
}

void MainWindow::on_pauseButton_clicked()
{
    remoteControl->sendMessage(ProtocolPacket::PAUSE, 0);
}

void MainWindow::on_muteButton_clicked()
{
    remoteControl->sendMessage(ProtocolPacket::SET_VOLUME_MUTE, QVariant::fromValue(ui->muteButton->isChecked()).toInt());
    if(ui->muteButton->isChecked())
    {
        ui->muteButton->setIcon(QIcon("://Images/mute.png"));
    } else
    {
        ui->muteButton->setIcon(QIcon("://Images/unmute.png"));
    }
}

void MainWindow::on_connectButton_clicked()
{
    remoteControl->connectToRemoteHost(ui->adressLineEdit->text());
}

void MainWindow::on_disconnectButtob_clicked()
{
    remoteControl->disconnectFromHost();
    ui->disconnectButtob->setEnabled(false);
    ui->connectButton->setEnabled(true);
}


void MainWindow::receiveMessage(ProtocolPacket packet)
{
    if(ui->connectButton->isEnabled())
    {
        ui->connectButton->setEnabled(false);
        ui->disconnectButtob->setEnabled(true);
    }

    //ui->logTextBrowser->append(QString::number(packet.command) + " " + QString::number(packet.value));

    switch(packet.command)
    {
    case ProtocolPacket::GET_VOLUME_MUTE:
    {
        ui->muteButton->setChecked(packet.value);
        break;
    }
    case ProtocolPacket::SET_VOLUME_MUTE:
    {
        ui->muteButton->setChecked(packet.value);
        break;
    }
    case ProtocolPacket::GET_SHUFFLE:
    {
        ui->shuffleButton->setChecked(packet.value);
        break;
    }
    case ProtocolPacket::SET_SHUFFLE:
    {
        ui->shuffleButton->setChecked(packet.value);
        break;
    }
    case ProtocolPacket::GET_VOLUME_LEVEL:
    {
        ui->volumeLevelLabel->setText(QString::number(packet.value));
        break;
    }
    case ProtocolPacket::SET_VOLUME_LEVEL:
    {
        ui->volumeLevelLabel->setText(QString::number(packet.value));
        break;
    }
    case ProtocolPacket::GET_POSITION:
    {
        ui->posotionLabel->setText(QString::number(packet.value));
        break;
    }
    case ProtocolPacket::GET_DURATION:
    {
        ui->durationLabel->setText(QString::number(packet.value));
        break;
    }
    case ProtocolPacket::GET_STATE:
    {
        switch(packet.value)
        {
        case ProtocolPacket::STATE_STOP:
        {
            ui->logTextBrowser->append("State is STOP");
            break;
        }
        case ProtocolPacket::STATE_PLAY:
        {
            ui->logTextBrowser->append("State is PLAY");
            break;
        }
        case ProtocolPacket::STATE_PAUSE:
        {
            ui->logTextBrowser->append("State is PAUSE");
            break;
        }
        }
        break;
    }
    case ProtocolPacket::GET_SYSTEM_MUTE:
    {
        ui->systemVolumeMuteButton->setChecked(packet.value);
        break;
    }
    case ProtocolPacket::SET_SYSTEM_MUTE:
    {
        ui->systemVolumeMuteButton->setChecked(packet.value);
        break;
    }
    case ProtocolPacket::GET_SYSTEM_VOLUME:
    {
        ui->systemVolumeLabel->setText(QString::number(packet.value));
        break;
    }
    case ProtocolPacket::SET_SYSTEM_VOLUME:
    {
        ui->systemVolumeLabel->setText(QString::number(packet.value));
        break;
    }
    }
}

void MainWindow::on_laLEft_clicked()
{
    remoteControl->sendMessage(ProtocolPacket::LA_LEFT, 0);
}

void MainWindow::on_laRight_clicked()
{
    remoteControl->sendMessage(ProtocolPacket::LA_RIGHT, 0);
}

void MainWindow::on_laFullScreen_clicked()
{
    remoteControl->sendMessage(ProtocolPacket::LA_FULLSCREEN, 0);
}

void MainWindow::on_laNotFull_clicked()
{
    remoteControl->sendMessage(ProtocolPacket::LA_NOT_FULLSCREEN, 0);
}

void MainWindow::on_laPlayButton_clicked()
{
    remoteControl->sendMessage(ProtocolPacket::LA_PLAY, 0);
}

void MainWindow::on_laPrevButton_clicked()
{
    remoteControl->sendMessage(ProtocolPacket::LA_PREV, 0);
}

void MainWindow::on_laNextButton_clicked()
{
    remoteControl->sendMessage(ProtocolPacket::LA_NEXT, 0);
}

void MainWindow::on_minusVolumeButton_clicked()
{
    int volumeLevel = ui->volumeLevelLabel->text().toInt() - 10;
    remoteControl->sendMessage(ProtocolPacket::SET_VOLUME_LEVEL, volumeLevel);
}

void MainWindow::on_plusVolumeButton_clicked()
{
    int volumeLevel = ui->volumeLevelLabel->text().toInt() + 10;
    remoteControl->sendMessage(ProtocolPacket::SET_VOLUME_LEVEL, volumeLevel);
}

void MainWindow::on_shutdownPcButton_clicked()
{
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Shutdown PC", "Are you sure?",
                                  QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        remoteControl->sendMessage(ProtocolPacket::PC_SHUTDOWN, 0);
    }
}

void MainWindow::on_shuffleButton_clicked()
{
    remoteControl->sendMessage(ProtocolPacket::SET_SHUFFLE, QVariant::fromValue(ui->shuffleButton->isChecked()).toInt());
}

void MainWindow::on_closeAimpButton_clicked()
{
    remoteControl->sendMessage(ProtocolPacket::QUIT, 1);
}

void MainWindow::on_launchAimpButton_clicked()
{
    remoteControl->sendMessage(ProtocolPacket::AIMP_LAUNCH, 1);
}

void MainWindow::on_sleepButton_clicked()
{
    remoteControl->sendMessage(ProtocolPacket::PC_SLEEP, 1);
}

void MainWindow::on_systemVolumeMuteButton_clicked()
{
    remoteControl->sendMessage(ProtocolPacket::SET_SYSTEM_MUTE, QVariant::fromValue(ui->systemVolumeMuteButton->isChecked()).toInt());
    if(ui->systemVolumeMuteButton->isChecked())
    {
        ui->systemVolumeMuteButton->setIcon(QIcon("://Images/mute.png"));
    } else
    {
        ui->systemVolumeMuteButton->setIcon(QIcon("://Images/unmute.png"));
    }
}

void MainWindow::on_systemVolumeMinusButton_clicked()
{
    int volumeLevel = ui->systemVolumeLabel->text().toInt() - 10;
    remoteControl->sendMessage(ProtocolPacket::SET_SYSTEM_VOLUME, volumeLevel);
}

void MainWindow::on_systemVolumePlusButton_clicked()
{
    int volumeLevel = ui->systemVolumeLabel->text().toInt() + 10;
    remoteControl->sendMessage(ProtocolPacket::SET_SYSTEM_VOLUME, volumeLevel);
}
