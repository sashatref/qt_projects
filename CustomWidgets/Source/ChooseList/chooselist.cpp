#include "chooselist.h"
#include "ui_chooselist.h"

#include "customlistwidgetitem.h"

ChooseList::ChooseList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChooseList)
{
    ui->setupUi(this);
}

ChooseList::~ChooseList()
{
    delete ui;
}

void ChooseList::setAllElementsList(QStringList valuesList)
{
    m_allElementsList = valuesList;

    ui->allElementsList->clear();

    for(int i = 0 ; i < valuesList.size(); i++)
    {
        ui->allElementsList->addItem(new CustomListWidgetItem(valuesList.at(i)));
    }

    ui->allElementsList->sortItems();

    emit allElementsListChanges(valuesList);
}

QStringList ChooseList::getAllElementsList()
{
    return m_allElementsList;
}

void ChooseList::setSelectedElementsList(QStringList valuesList)
{
    m_currentElementsList = valuesList;

    ui->currentElementList->clear();

    for(int i = 0, total = m_currentElementsList.size(); i < total; ++i)
    {
        if(m_allElementsList.contains(m_currentElementsList.at(i)))
        {
            ui->currentElementList->addItem(new CustomListWidgetItem(m_currentElementsList.at(i)));
        }

        for(int j = 0; j < m_allElementsList.size(); j++)
        {
            QListWidgetItem *item = ui->allElementsList->item(j);
            if(item->text() == m_currentElementsList.at(i))
            {
                delete item;
                break;
            }
        }
    }

    ui->currentElementList->sortItems();

    emit selectedElementsListChanged(m_currentElementsList);
}

QStringList ChooseList::getSelectedElementsList()
{
    return m_currentElementsList;
}

QFont ChooseList::labelsFont()
{
    return ui->allElementsLabel->font();
}

void ChooseList::setLabelsFont(QFont value)
{
    ui->allElementsLabel->setFont(value);
    ui->selectedElementsLabel->setFont(value);
}

void ChooseList::setListFont(QFont value)
{
    ui->allElementsList->setFont(value);
    ui->currentElementList->setFont(value);
}

QFont ChooseList::listFont()
{
    return ui->allElementsList->font();
}

void ChooseList::translate()
{
    ui->addItemButton->setText(tr("Add"));
    ui->addItemButton->setToolTip(tr("Add"));
    ui->removeItemButton->setText(tr("Remove"));
    ui->removeItemButton->setToolTip(tr("Remove"));
}

void ChooseList::on_addItemButton_clicked()
{
    for(int i = ui->allElementsList->selectedItems().count() - 1; i > -1; i--)
    {
        ui->currentElementList->addItem(new CustomListWidgetItem(ui->allElementsList->selectedItems().at(i)->text()));
        emit itemAdded(ui->allElementsList->selectedItems().at(i)->text());
        delete ui->allElementsList->selectedItems().at(i);
    }
    ui->currentElementList->sortItems();

    QStringList values;

    for(int i = 0; i < ui->currentElementList->count(); i++)
    {
        values.append(ui->currentElementList->item(i)->text());
    }

    ui->currentElementList->sortItems();

    emit selectedElementsListChanged(values);
}

void ChooseList::on_removeItemButton_clicked()
{
    for(int i = ui->currentElementList->selectedItems().count() - 1; i > -1; i--)
    {
        ui->allElementsList->addItem(new CustomListWidgetItem(ui->currentElementList->selectedItems().at(i)->text()));
        emit itemRemoved(ui->currentElementList->selectedItems().at(i)->text());
        delete ui->currentElementList->selectedItems().at(i);
    }
    ui->allElementsList->sortItems();

    QStringList values;

    for(int i = 0; i < ui->currentElementList->count(); i++)
    {
        values.append(ui->currentElementList->item(i)->text());
    }

    ui->allElementsList->sortItems();

    emit selectedElementsListChanged(values);
}
