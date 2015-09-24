#pragma once

#include <QWidget>
#include "extcombotype.h"
#include "../CustomWidgets_pch.h"

class QComboBox;
class QToolButton;
class WIDGET_EXPORT ExtComboEdit : public QWidget
{
    Q_OBJECT
public:
     ExtComboEdit(QWidget *parent = 0);

     void setValuesList(QStringList values);
     QStringList valuesList();

     void setCurrentValue(QString value);
     QString currentValue();

     void setType(int value);
     int getType();

public slots:
     void addComboItem(QString item);
     void removeComboItem(QString item);
     void editComboItem(QString item);

private:
    QComboBox *m_combo;
    QToolButton *m_addButton, *m_openButton;
    int m_type;

signals:
    void addClicked(QString, int type, ExtComboEdit *editor);
    void addClicked();
    void openClicked();
    void openClicked(QString, int type, ExtComboEdit *editor);

private slots:
    void onAddClick();
    void onOpenClick();
};
