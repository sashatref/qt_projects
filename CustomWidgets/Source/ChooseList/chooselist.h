#pragma once
#include <QWidget>
#include "../CustomWidgets_pch.h"

namespace Ui {
class ChooseList;
}

class WIDGET_EXPORT ChooseList : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QStringList getAllElementsList READ getAllElementsList WRITE setAllElementsList)
    Q_PROPERTY(QStringList getSelectedElementsList READ getSelectedElementsList WRITE setSelectedElementsList)
    Q_PROPERTY(QFont labelsFont READ labelsFont WRITE setLabelsFont)
    Q_PROPERTY(QFont listFont READ listFont WRITE setListFont)
public:
    ChooseList(QWidget *parent = 0);
    ~ChooseList();

    void setAllElementsList(QStringList valuesList);
    QStringList getAllElementsList();

    void setSelectedElementsList(QStringList valuesList);
    QStringList getSelectedElementsList();

    QFont labelsFont();
    void setLabelsFont(QFont value);

    void setListFont(QFont value);
    QFont listFont();

    void translate();

signals:
    void allElementsListChanges(QStringList values);
    void selectedElementsListChanged(QStringList values);
    void itemAdded(QString item);
    void itemRemoved(QString item);

private slots:
    void on_addItemButton_clicked();
    void on_removeItemButton_clicked();

private:
    Ui::ChooseList *ui;

    QStringList m_allElementsList;
    QStringList m_currentElementsList;
};
