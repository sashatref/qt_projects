#pragma once

#include <QStandardItem>
#include <QDateTime>

/*!
 * \brief QStandartItem с переопределенном методом сравнения
 * для добавления элементов в QTableView с датами-временем.
 * Что даст адекватную сортировку по дата-время
 */

class DateTimeItem : public QStandardItem
{
public:
    DateTimeItem(QString text) : QStandardItem(text) {}
protected:
    bool operator <(const QStandardItem &other) const
    {
        return (QDateTime::fromString(this->text(), "dd-MM-yyyy hh:mm")  < QDateTime::fromString(other.text(), "dd-MM-yyyy hh:mm"));
    }
};


