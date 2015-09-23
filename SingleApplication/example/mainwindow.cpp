#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_nAppLanched(0)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::anotherAppInstanceLaunch()
{
    m_nAppLanched++;
    ui->label->setText("Попыток: " + QString::number(m_nAppLanched));
}
