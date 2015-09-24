#pragma once

#include <QStandardItem>

/*!
 * \brief QStandartItem с переопределенном методом сравнения
 * для добавления элементов в QTableView с числами.
 * Что даст адекватную сортировку по числам
 */

class IntItem : public QStandardItem
{
public:
    IntItem(QString text) : QStandardItem(text){}
protected:
    bool operator <(const QStandardItem &other) const
    {
        return (this->text().toInt() < other.text().toInt());
    }
};
