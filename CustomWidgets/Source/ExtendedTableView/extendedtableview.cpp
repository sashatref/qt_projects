#include "extendedtableview.h"
#include "ui_extendedtableview.h"

#include <QDebug>
#include <QMessageBox>
#include <QKeyEvent>

#include "filterwidget.h"

ExtendedtableView::ExtendedtableView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ExtendedtableView)
{
    ui->setupUi(this);
    ui->splitter->setSizes(QList<int>() << 140 << 400);

    ui->myTableView->horizontalHeader()->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->myTableView->horizontalHeader(), SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showContextMenu(QPoint)));
    ui->myTableView->installEventFilter(this);
}

ExtendedtableView::~ExtendedtableView()
{
    delete ui;
}

void ExtendedtableView::on_savePresetButton_clicked()
{
    //просматриваем список из ListWidget и заполняем карту значениями true/false(checked/unchecked)
    QMap<QString, bool> presetToSave;
    for(int i = 0; i < ui->listWidget->count(); i++)
    {
        if(ui->listWidget->item(i)->checkState() == Qt::Checked)
        {
            presetToSave[ui->listWidget->item(i)->data(Qt::UserRole).toString()] = true;
        } else {
            presetToSave[ui->listWidget->item(i)->data(Qt::UserRole).toString()] = false;
        }
    }

    //сохраняем данные пресет в общую карту пресетов
    m_presetsMap[ui->comboBox->currentText()] = presetToSave;

    //добавляем пресет в комбобокс и устанавливаем его как currentIndex

    QString currentPreset = ui->comboBox->currentText();
    ui->comboBox->clear();
    for(int i = 0; i < m_presetsMap.count(); i++)
    {
        ui->comboBox->addItem(m_presetsMap.keys().at(i));
    }
    ui->comboBox->setCurrentText(currentPreset);
}

void ExtendedtableView::on_removePresetButton_clicked()
{
    //если вписан текст, а пресета нет, то выдаем предупреждение
    if(!m_presetsMap.keys().contains(ui->comboBox->currentText()))
    {
        QMessageBox::information(this, tr("Внимание!"), tr("Выбрана некорректная предустановка!"));
        return;
    }

    //запрос, действительно ли хотим удалть
    QMessageBox::StandardButton resBtn = QMessageBox::question(this,
                                                               tr("Внимание!"),
                                                               tr("Удалить предустановку ") + ui->comboBox->currentText() +" ?",
                                                               QMessageBox::Cancel | QMessageBox::Yes,
                                                               QMessageBox::Yes);

    if (resBtn != QMessageBox::Yes) { return; }

    //удаляем выбранные пресет из карты пресетов и из списка элементов комбобокса
    if(m_presetsMap.keys().contains(ui->comboBox->currentText()))
    {
        m_presetsMap.remove(ui->comboBox->currentText());
        ui->comboBox->removeItem(ui->comboBox->currentIndex());
        ui->comboBox->activated(ui->comboBox->currentText());
    }
}

void ExtendedtableView::on_comboBox_activated(const QString &arg1)
{
    //если выбран существующий пресет, то загружаем его

    if(m_presetsMap.contains(arg1))
    {
        _setChecked(m_presetsMap[arg1]);
    } else //если пресет в список был добавлен по нажатию enter, то удаляем его из списка,
        //автоматически будет выбран и активирован последний в списке существующий пресет
    {
        ui->comboBox->removeItem(ui->comboBox->currentIndex());
    }
}

void ExtendedtableView::showContextMenu(QPoint point)
{
    //считаем номер колонки по координатам
    int column = ui->myTableView->columnAt(point.x());
    QPoint globalPos = ui->myTableView->mapToGlobal(point);

    QMap<QString, bool> allTextValues = getValuesForColumn(column);

    FilterWidget filter(this);
    filter.move(globalPos);
    filter.setWindowFlags(Qt::Popup);
    filter.setColumn(column);
    filter.setValues(allTextValues);
    connect(&filter, SIGNAL(filterListChanged(int,QMap<QString,bool>)), this, SLOT(filterWidgetOkClicked(int,QMap<QString,bool>)));
    filter.exec();
}

void ExtendedtableView::onItemChange(QListWidgetItem *changedItem)
{
    int index = ui->listWidget->row(changedItem);
       if(changedItem->checkState() == Qt::Checked)
       {
           ui->myTableView->showColumn(index);
       } else
       {
           ui->myTableView->hideColumn(index);
           QStringList keys = valuesToFilter[index].keys();
           for(int i = 0; i < keys.count(); i++)
           {
               valuesToFilter[index][keys.at(i)] = true;
           }
           onFilterChanged(ui->myTableView, valuesToFilter);
       }
}

void ExtendedtableView::onFilterChanged(MyTableView *table, QMap<int, QMap<QString, bool>> mapToFilter)
{
    for(int j = 0; j < table->model()->rowCount(); j++)
    {
        for(int i = 0; i < table->horizontalHeader()->count(); i++)
        {
            QModelIndex modelIndex = table->model()->index(j, i);
            QString text = table->model()->data(modelIndex, Qt::DisplayRole).toString();
            if(text == "") text = tr("(пустое)");
            bool res = mapToFilter[i].keys().contains(text);
            if(res)
            {
                res = mapToFilter[i][text];
                if(res)
                {
                    table->showRow(j);
                } else
                {
                    table->hideRow(j);
                    break;
                }
            } else
            {
                table->showRow(j);
            }
        }
    }
}

void ExtendedtableView::filterWidgetOkClicked(int column, QMap<QString, bool> mapToFilter)
{
    valuesToFilter[column] = mapToFilter;
    onFilterChanged(ui->myTableView, valuesToFilter);
}


void ExtendedtableView::initList()
{
    //очищаем список
    ui->listWidget->clear();

    //перебираем все названия горизонтального ходера и добавляем элементы в listWidget
    for(int i = 0; i < ui->myTableView->horizontalHeader()->count(); i++)
    {
        QString headerText = ui->myTableView->model()->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString();
        QListWidgetItem *listItem = new QListWidgetItem();
        listItem->setText(headerText);
        QVariant var = ui->myTableView->model()->headerData(i, Qt::Horizontal, Qt::UserRole);

        if(!var.isValid())
        {
            qDebug() << "Element at: " << i << " hasn't UserRole data! Presets will no work!";
        }

        listItem->setData(Qt::UserRole, var);
        ui->listWidget->addItem(listItem);
    }

    //для всех элементов listWidget ставим статус Checked, вроде ID
    for(int i = 0; i < ui->listWidget->count(); i++)
    {
        ui->listWidget->item(i)->setCheckState(Qt::Checked);
    }
    //при смене состояния Checked прям или показываем соответствующую колонку
    connect(ui->listWidget, SIGNAL(itemChanged(QListWidgetItem*)), this, SLOT(onItemChange(QListWidgetItem*)));

    if(m_presetsMap.contains(ui->comboBox->currentText()))
    {
        _setChecked(m_presetsMap[ui->comboBox->currentText()]);
    }
}


QMap<QString, bool> ExtendedtableView::getValuesForColumn(int column)
{
    QStringList valuesList;
    QMap<QString, bool> valuesMap;

    if(column > ui->myTableView->horizontalHeader()->count() - 1)
    {
        return valuesMap;
    }

    //получаем все варианты записей со всех строк,

    for(int i = 0; i < ui->myTableView->model()->rowCount(); i++)
    {
        QString cellValue = ui->myTableView->model()->data(ui->myTableView->model()->index(i, column), Qt::DisplayRole).toString();

        if(cellValue == "")
        {
            if(!valuesList.contains(tr("(пустое)"))) { valuesList.append(tr("(пустое)")); }
        }
        else
        {
            if(!valuesList.contains(cellValue)) { valuesList.append(cellValue); }
        }
    }


    //формируем словарь, если раньше уже были отмечены какие-то строки, то их учитываем.
    for(int i = 0 ; i < valuesList.size(); i++)
    {
        if(valuesToFilter[column].contains(valuesList.at(i)))
        {
            valuesMap[valuesList.at(i)] = valuesToFilter[column][valuesList.at(i)];
        } else
        {
            valuesMap[valuesList.at(i)] = true;
        }
    }

    return valuesMap;
}

bool ExtendedtableView::eventFilter(QObject *object, QEvent *event)
{
    if(object == ui->myTableView && event->type() == QEvent::KeyPress)
    {
        QKeyEvent *keyEvent = (QKeyEvent*)event;
        if(keyEvent->key() == Qt::Key_Delete)
        {
            emit deleteKeyEvent();
        }
    }
    return QObject::eventFilter(object, event);
}



MyTableView *ExtendedtableView::_table() const
{
    return ui->myTableView;
}

QWidget *ExtendedtableView::_controlWidget() const
{
    return ui->verticalLayoutWidget;
}

void ExtendedtableView::_init()
{
    initList();
}

void ExtendedtableView::_setCheckAll(bool _isChecked)
{
    for(int i = 0; i < ui->listWidget->count(); i++)
    {
        if(_isChecked && !m_rowsToHide.contains(ui->listWidget->item(i)->data(Qt::UserRole).toString()))
        {
            ui->listWidget->item(i)->setCheckState(Qt::Checked);
        }
        else {ui->listWidget->item(i)->setCheckState(Qt::Unchecked);}
    }
}

void ExtendedtableView::_setChecked(QMap<QString, bool> _namesToCheck)
{
    for(int i = 0; i < ui->listWidget->count(); i++)
    {
        if(_namesToCheck.keys().contains(ui->listWidget->item(i)->data(Qt::UserRole).toString()))
        {
            if(_namesToCheck[ui->listWidget->item(i)->data(Qt::UserRole).toString()])
            {
                ui->listWidget->item(i)->setCheckState(Qt::Checked);
            } else
            {
                ui->listWidget->item(i)->setCheckState(Qt::Unchecked);
            }
        }
    }
}

void ExtendedtableView::_setPresetList(QMap<QString, QMap<QString, bool> > _mapOfPresets)
{
    m_presetsMap = _mapOfPresets;

    ui->comboBox->clear();
    ui->comboBox->addItems(m_presetsMap.keys());
}

QMap<QString, QMap<QString, bool> > ExtendedtableView::_presetList()
{
    return m_presetsMap;
}

QString ExtendedtableView::_currentPreset()
{
    return ui->comboBox->itemText(ui->comboBox->currentIndex());
}

void ExtendedtableView::_setCurrentPreset(QString _currentPreset)
{
    for(int i = 0 ; i < ui->comboBox->count(); i++)
    {
        if(ui->comboBox->itemText(i) == _currentPreset)
        {
            ui->comboBox->setCurrentIndex(i);
            ui->comboBox->activated(_currentPreset);
            break;
        }
    }
}

void ExtendedtableView::translate()
{

}

/*------------------my table view forwarding------------*/
/*------------------------------------------------------*/

void ExtendedtableView::setBackgroundOpacity(double value)
{
    ui->myTableView->setBackgroundOpacity(value);
}

double ExtendedtableView::backgroundOpacity() const
{
    return ui->myTableView->getBackGroundOpacity();
}

void ExtendedtableView::setBackgroundPixmap(QPixmap value)
{
    ui->myTableView->setBackgroundPixmap(value);
}

QPixmap ExtendedtableView::backgroundPixmap() const
{
    return ui->myTableView->getBackgroundPixmap();
}

void ExtendedtableView::setVerticalPadding(int value)
{
    ui->myTableView->setVerticalPadding(value);
}

int ExtendedtableView::verticalPadding() const
{
    return ui->myTableView->getVericalPadding();
}

void ExtendedtableView::setHorizontalPadding(int value)
{
    ui->myTableView->setHorizontalPadding(value);
}

int ExtendedtableView::horizontalPadding() const
{
    return ui->myTableView->getHorizontalPadding();
}

QStringList ExtendedtableView::rowsToHide()
{
    return m_rowsToHide;
}

void ExtendedtableView::setRowsToHide(QStringList _namesToHide)
{
    m_rowsToHide = _namesToHide;
    for(int i = 0; i < ui->listWidget->count(); i++)
    {
        if(_namesToHide.contains(ui->listWidget->item(i)->data(Qt::UserRole).toString()))
        {
            ui->listWidget->item(i)->setCheckState(Qt::Unchecked);
            ui->listWidget->setRowHidden(i, true);
        } else
        {
            ui->listWidget->setRowHidden(i, false);
        }
    }
}

void ExtendedtableView::setColumnsContolVisible(bool _visible)
{
    ui->verticalLayoutWidget->setVisible(_visible);
}

void ExtendedtableView::setPresetControlVisible(bool _visible)
{
    ui->savePresetButton->setVisible(_visible);
    ui->removePresetButton->setVisible(_visible);
    ui->comboBox->setVisible(_visible);
}

bool ExtendedtableView::columnControlVisible()
{
    return ui->verticalLayoutWidget->isVisible();
}

bool ExtendedtableView::presetControlVisible()
{
    return ui->savePresetButton->isVisible();
}

/*------------------/my table view forwarding------------*/
/*------------------------------------------------------*/
