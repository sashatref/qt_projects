#include "smartlist.h"
#include "ui_smartlist.h"

SmartList::SmartList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SmartList)
{
    ui->setupUi(this);
}

SmartList::~SmartList()
{
    delete ui;
}

QSize SmartList::iconSize()
{
    return ui->addButton->iconSize();
}

void SmartList::setIconSize(QSize value)
{
    ui->addButton->setIconSize(value);
    ui->editButton->setIconSize(value);
    ui->removeButton->setIconSize(value);
}

QFont SmartList::listFont()
{
    return ui->listWidget->font();
}

void SmartList::setListFont(QFont value)
{
    ui->listWidget->setFont(value);
}

void SmartList::on_addButton_clicked()
{
    QListWidgetItem *item = new QListWidgetItem();
    ui->listWidget->addItem(item);
    item->setFlags(item->flags() | Qt::ItemIsEditable | Qt::ItemIsSelectable);
    item->setText("enter value");
    ui->listWidget->editItem(item);
}

void SmartList::on_editButton_clicked()
{

}

void SmartList::on_removeButton_clicked()
{

}
