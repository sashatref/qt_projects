#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include "testobject.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->propertyBrowser->setListener(this);
    ui->propertyBrowser->setCreateObjectType(PropertyType::TestObjectId());
}

MainWindow::~MainWindow()
{
    delete ui;
}

QVariant MainWindow::OnGetNewObject(int _objectTypeToCreate)
{
    QVariant var;

    if(_objectTypeToCreate == PropertyType::TestObjectId())
    {
        var = QVariant::fromValue(TestObject());
    } else if(_objectTypeToCreate == PropertyType::MyClassId())
    {
        var = QVariant::fromValue(MyClass());
    }

    return var;
}

void MainWindow::on_loadButton_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, "Select file to load...");
    if(path.isEmpty())
    {
        return;
    }

    QFile file(path);
    if(file.open(QIODevice::ReadOnly))
    {
        QDataStream stream(&file);

        QVariantList list;
        stream >> list;

        ui->propertyBrowser->setVariantList(list);

        file.close();
    }
}

void MainWindow::on_saveButton_clicked()
{
    QString path = QFileDialog::getSaveFileName(this, "Select file to save...");
    if(path.isEmpty())
    {
        return;
    }

    QFile file(path);
    if(file.open(QIODevice::WriteOnly))
    {
        QDataStream stream(&file);

        QVariantList list = ui->propertyBrowser->getVariantList();
        stream << list;

        file.close();
    }
}
