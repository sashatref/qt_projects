#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "propertybrowser.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow, public PropertyBrowserListener
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QVariant OnGetNewObject(int _objectTypeToCreate) override;

private slots:
    void on_loadButton_clicked();
    void on_saveButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
