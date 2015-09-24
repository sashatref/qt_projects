#pragma once

#include <QWidget>
#include <QListWidgetItem>
#include "../CustomWidgets_pch.h"

class MyTableView;
namespace Ui {
class ExtendedtableView;
}

/*!
 * \brief расширенная версия Таблицы с возможностью установки фонового изоражения
 * использования фильтров для отображения нужных строк
 * показ QListWidget, в котором можно выбирать колонки для отображения,
 * с возможностью сохраннения пресетов
 */

class WIDGET_EXPORT ExtendedtableView : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(bool columnControlVisible READ columnControlVisible WRITE setColumnsContolVisible)
    Q_PROPERTY(bool presetControlVisible READ presetControlVisible WRITE setPresetControlVisible)
    Q_PROPERTY(QStringList rowsToHide READ rowsToHide WRITE setRowsToHide)

    Q_PROPERTY(double backgroundOpacity READ backgroundOpacity WRITE setBackgroundOpacity)
    Q_PROPERTY(QPixmap backgroundPixmap READ backgroundPixmap WRITE setBackgroundPixmap)
    Q_PROPERTY(int verticalPadding READ verticalPadding WRITE setVerticalPadding)
    Q_PROPERTY(int horizontalPadding READ horizontalPadding WRITE setHorizontalPadding)

public:
    /*------------------my table view forwarding------------*/
    /*------------------------------------------------------*/
    void setBackgroundOpacity(double value);
    double backgroundOpacity() const;

    void setBackgroundPixmap(QPixmap value);
    QPixmap backgroundPixmap() const;

    void setVerticalPadding(int value);
    int verticalPadding() const;

    void setHorizontalPadding(int value);
    int horizontalPadding() const;
    /*------------------/my table view forwarding------------*/
    /*------------------------------------------------------*/

    QStringList rowsToHide();
    void setRowsToHide(QStringList _namesToHide);
    void setColumnsContolVisible(bool _visible);
    void setPresetControlVisible(bool _visible);
    bool columnControlVisible();
    bool presetControlVisible();

    //возвращаем ссылку на таблицу
    MyTableView *_table() const;
    QWidget *_controlWidget() const;

    //формирует виджет с выбором колонок и загрузки
    void _init();

    void _setCheckAll(bool _isChecked);
    void _setChecked(QMap<QString, bool> _namesToCheck);
    void _setPresetList(QMap<QString, QMap<QString, bool>> _mapOfPresets);
    QMap<QString, QMap<QString, bool>> _presetList();
    QString _currentPreset();
    void _setCurrentPreset(QString _currentPreset);

    void translate();

    ExtendedtableView(QWidget *parent = 0);
    ~ExtendedtableView();

signals:
    void deleteKeyEvent();

private slots:
    void on_savePresetButton_clicked();
    void on_removePresetButton_clicked();
    void on_comboBox_activated(const QString &arg1);

    void showContextMenu(QPoint point);

    void onItemChange(QListWidgetItem* changedItem);

    static void onFilterChanged(MyTableView *table, QMap<int, QMap<QString, bool>> mapToFilter);

    void filterWidgetOkClicked(int column, QMap<QString, bool> mapToFilter);

private:
    Ui::ExtendedtableView *ui;

    QStringList m_rowsToHide;
    QMap<QString, QMap<QString, bool>> m_presetsMap;
    QMap<int, QMap<QString, bool>> valuesToFilter;

    void initList();

    QMap<QString, bool> getValuesForColumn(int column);

protected:
    bool eventFilter(QObject *object, QEvent *event);
};
