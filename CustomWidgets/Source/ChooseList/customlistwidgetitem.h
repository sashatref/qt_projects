#pragma once

#include <QListWidgetItem>

class CustomListWidgetItem : public QListWidgetItem
{
public:
    CustomListWidgetItem(QString text) : QListWidgetItem(text) {}

protected:
    bool operator <(const QListWidgetItem &other) const
    {
        int firstIndex = this->text().left(this->text().indexOf(".")).toInt();
        int secondIndex = other.text().left(other.text().indexOf(".")).toInt();
        return firstIndex < secondIndex;
    }
};

