#pragma once

#include <QDialog>
#include <QListWidgetItem>

namespace Ui {
class FilterWidget;
}

/*!
 * \brief виджет, для выбора колонок таблицы, которые будут отображаться(установка фильтров)
 */

class FilterWidget : public QDialog
{
    Q_OBJECT
public:
    FilterWidget(QWidget *parent = 0);
    ~FilterWidget();


    void setColumn(int number);
    void setValues(QMap<QString, bool> valuesList);

signals:
    void filterListChanged(int, QMap<QString, bool>);

private slots:
    void onFilterItemChange(QListWidgetItem *changedItem);

    void on_okButton_clicked();
    void on_cancelButton_clicked();

private:
    Ui::FilterWidget *ui;
    int currentColumn;
};
