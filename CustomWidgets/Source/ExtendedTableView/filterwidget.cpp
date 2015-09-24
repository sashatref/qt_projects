#include "filterwidget.h"
#include "ui_filterwidget.h"

FilterWidget::FilterWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FilterWidget)
{
    ui->setupUi(this);
    connect(ui->listWidget, SIGNAL(itemChanged(QListWidgetItem*)), this, SLOT(onFilterItemChange(QListWidgetItem*)));
    currentColumn = -1;
}

FilterWidget::~FilterWidget()
{
    delete ui;
}

void FilterWidget::setColumn(int number)
{
    currentColumn = number;
}

void FilterWidget::setValues(QMap<QString, bool> valuesList)
{
    ui->listWidget->clear();

//    QListWidgetItem *item = new QListWidgetItem(ui->listWidget);
//    item->setText("Select all");
//    item->setCheckState(Qt::Checked);

    for(int i = 0; i < valuesList.keys().size(); i++)
    {
        QString text = valuesList.keys().at(i);
        QListWidgetItem *item = new QListWidgetItem(ui->listWidget);
        item->setText(text);
        if(valuesList[text])
        {
            item->setCheckState(Qt::Checked);
        } else
        {
            item->setCheckState(Qt::Unchecked);
        }
    }
}

void FilterWidget::onFilterItemChange(QListWidgetItem*)
{
//    if(changedItem->text() == tr("Select all"))
//    {
//        for(int i = 0; i < ui->listWidget->count(); i++)
//        {
//            ui->listWidget->item(i)->setCheckState(changedItem->checkState());
//        }
//    }
}

void FilterWidget::on_okButton_clicked()
{
    QMap<QString, bool> checkedMap;
    for(int i = 0; i < ui->listWidget->count(); i++)
    {
        QListWidgetItem *item = ui->listWidget->item(i);

        //if(item->text() == "Select all") continue;

        if(item->checkState() == Qt::Checked)
        {
            checkedMap[item->text()] = true;
        } else
        {
            checkedMap[item->text()] = false;
        }
    }

    emit filterListChanged(currentColumn, checkedMap);
    this->close();
}

void FilterWidget::on_cancelButton_clicked()
{
    this->close();
}
