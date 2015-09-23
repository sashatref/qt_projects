#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mytcpserver.h"
#include <QSystemTrayIcon>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void hideOnStartUp();

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void on_actionExit_triggered();

    void on_actionCl_ear_log_triggered();
    void tray_clicked(QSystemTrayIcon::ActivationReason action);
    void tray_showClicked();
    void clientConnected(QString text);

    void on_selectAimpPathButton_clicked();
    void receiveMessage();

    void on_action_autoStart_triggered(bool checked);

private:
    Ui::MainWindow *ui;
    MyTCPServer *m_server;
    QSystemTrayIcon *m_trayIcon;

    bool isReallyClose;

    bool checkForAutoStart();
    void setAutoStart(bool _enable);
};

#endif // MAINWINDOW_H
