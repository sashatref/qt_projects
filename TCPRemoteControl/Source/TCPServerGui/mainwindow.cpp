#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QCloseEvent>
#include <QSettings>
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QSettings settings("settings.ini", QSettings::IniFormat);
    ui->aimpPathLineEdit->setText(settings.value("aimp_path", "").toString());

    m_server = new MyTCPServer(44405, ui->logTextBrowser, this);
    m_server->setAimpPath(ui->aimpPathLineEdit->text());
    connect(m_server, SIGNAL(clientConnected(QString)), this, SLOT(clientConnected(QString)));

    m_trayIcon = new QSystemTrayIcon(QIcon(":/icon.png"));
    connect(m_trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(tray_clicked(QSystemTrayIcon::ActivationReason)));

    isReallyClose = false;

    ui->action_autoStart->setChecked(checkForAutoStart());
}

MainWindow::~MainWindow()
{
    QSettings settings("settings.ini", QSettings::IniFormat);
    settings.setValue("aimp_path", ui->aimpPathLineEdit->text());
    delete m_server;
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(!m_trayIcon->isVisible() && !isReallyClose)
    {
        m_trayIcon->show();
        event->ignore();
        this->hide();
    }
}

void MainWindow::on_actionExit_triggered()
{
    isReallyClose = true;
    this->close();
}

void MainWindow::on_actionCl_ear_log_triggered()
{
    ui->logTextBrowser->clear();
}

void MainWindow::tray_clicked(QSystemTrayIcon::ActivationReason action)
{
    if(action == QSystemTrayIcon::Trigger)
    {
        m_trayIcon->hide();
        this->show();
    } else if(action == QSystemTrayIcon::Context)
    {
        QMenu *trayIconMenu = new QMenu(this);

        QAction *action = new QAction("Show", trayIconMenu);
        connect(action, SIGNAL(triggered()),this, SLOT(tray_showClicked()));
        trayIconMenu->addAction(action);
        trayIconMenu->addSeparator();
        trayIconMenu->addAction(ui->actionExit);

        m_trayIcon->setContextMenu(trayIconMenu);
    }
}

void MainWindow::tray_showClicked()
{
    m_trayIcon->hide();
    this->show();
}

void MainWindow::clientConnected(QString text)
{
    if(m_trayIcon->isVisible())
    {
        m_trayIcon->showMessage("Connected", text);
    }
}

void MainWindow::on_selectAimpPathButton_clicked()
{
    QString res = "";
    res = QFileDialog::getOpenFileName(this, "Select aimp.exe", ui->aimpPathLineEdit->text(), "AIMP3.exe");
    if(res != "")
    {
        ui->aimpPathLineEdit->setText(res);
    }
}

void MainWindow::receiveMessage()
{
    tray_showClicked();
}

void MainWindow::hideOnStartUp()
{
    m_trayIcon->show();
    this->hide();
}



bool MainWindow::checkForAutoStart()
{
    QSettings autorun("HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run",QSettings::NativeFormat);
    if(autorun.value("TCPRemoteControl", "") == "")
    {
        return false;
    }

    return true;
}

void MainWindow::setAutoStart(bool _enable)
{
    QSettings autorun("HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run",QSettings::NativeFormat);
    if(_enable)
    {
        autorun.setValue("TCPRemoteControl", QDir::toNativeSeparators(QCoreApplication::applicationFilePath()) + " -hidden");
        autorun.sync();
    }
    else
    {
        autorun.remove("TCPRemoteControl");
    }
}

void MainWindow::on_action_autoStart_triggered(bool checked)
{
    setAutoStart(checked);
}
