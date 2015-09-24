#pragma once

#include <QStandardItem>
#include <QDate>

/*!
 * \brief QStandartItem с переопределенном методом сравнения
 * для добавления элементов в QTableView с датами.
 * Что даст адекватную сортировку по датам
 */

class DateItem : public QStandardItem
{
public:
    DateItem(QString text) : QStandardItem(text){}
protected:
    bool operator <(const QStandardItem &other) const
    {
        return (QDate::fromString(this->text(), "dd-MM-yyyy")  < QDate::fromString(other.text(), "dd-MM-yyyy"));
    }
};

