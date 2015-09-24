#pragma once

#include <QWidget>
#include <QListWidgetItem>
#include "../CustomWidgets_pch.h"

namespace Ui {
class SmartList;
}

class WIDGET_EXPORT SmartList : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QSize iconSize READ iconSize WRITE setIconSize)
    Q_PROPERTY(QFont listFont READ listFont WRITE setListFont)
public:
    QSize iconSize();
    void setIconSize(QSize value);

    QFont listFont();
    void setListFont(QFont value);

    SmartList(QWidget *parent = 0);
    ~SmartList();

signals:
    void valueAdd(QString);
    void valueAdd(QListWidgetItem *item);

    void valueRemove(QString);

    void valueEdited(QString);
    void valueEdited(QListWidgetItem *item);

    void itemSelected(QString);
    void itemSelected(int index);

private slots:
    void on_addButton_clicked();
    void on_editButton_clicked();
    void on_removeButton_clicked();

private:
    Ui::SmartList *ui;

};


