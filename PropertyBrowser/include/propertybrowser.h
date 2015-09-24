#pragma once

#include <QDialog>
#include <QMap>
#include <QVariant>
#include "propertyinfo.h"

#if defined(PROPERTYBROWSER)
#  define PROPERTYBROWSER_EXPORT __declspec(dllexport)
#else
#  define PROPERTYBROWSER_EXPORT
#endif

namespace Ui {
class PropertyBrowser;
}

class PropertyBrowserListener
{
public:
    /*!
     * \brief callback функция, которая вызывается при нажатие кнопки "Add"
     * \param _objectTypeToCreate тип создаваемого объекта, это значение
     * устанавливается пользователем для всего PropertyBrowser
     * \return QVariant содержащий пустой объект или указатель на него
     */
    virtual QVariant OnGetNewObject(int _objectTypeToCreate) { _objectTypeToCreate; return 0;}

    /*!
     * \brief callback функции, которая вызывается при нажатие кнопки "Remove"
     * и при уничтожение PropertyBrowser
     * \param _object объект которые пользователь должен удалить или оставить как есть
     * (удалять нужно, если в OnGetNewObject добавляются указатели на объекты)
     * \param _objectTypeToCreate тип создаваемого объекта, это значение устанавливается
     * пользователем для всего PropertyBrowser
     */
    virtual void OnObjectDelete(const QVariant &_object, int _objectTypeToCreate) {&_object; &_objectTypeToCreate;}

    /*!
     * \brief секция функции, необходимых для создание пользовательских редакторок для
     * неизвестных типов свойств
     */
    virtual QWidget *createCustomEditor(QString _propertyName, QString _objectName, QWidget *_parent)
    {&_propertyName; &_objectName; &_parent; return 0;}
    virtual void setCustomEditorData(QString _propertyName, QString _objectName, QWidget *_widget, QVariant _value)
    { &_propertyName; &_objectName; &_widget; &_value; }
    virtual QVariant saveCustomEditorData(QString _propertyName, QString _objectName, QWidget *_widget)
    {&_propertyName; &_objectName; &_widget;return QVariant();}
    virtual QString updateCustomEditorTextValue(QString _propertyName, QString _objectName, QVariant _value)
    {&_propertyName; &_objectName; &_value; return QString();}
    virtual void updateCustomEditorGeometry(QString _propertyName, QString _objectName, QWidget *_widget)
    {&_propertyName; &_objectName; &_widget;}
};

class ItemDelegate;
class AbstractPropertyItem;
class QTreeWidgetItem;
class QListWidgetItem;
class QListWidget;

/*!
 * \brief The PropertyBrowser class
 * Предназначен для редактирования свойств классов
 * значения для редактирования устанавливаются функциями setVariant, setVariantList
 * в передаваемый QVariant можно запихнуть любой объект, главное ддля него должен быть
 * зарегестрирован конвертер в тип QObject*
 * Для указания параметров отображения каждого свойства, используется класс PropertyInfo
 * Для того чтоб его передать в PropertyBrowser, для класса должен быть зарегестирован
 * конвертер в PropertyInfoMapType
 *
 * Есть возможность использования своих редакторов для неизвестных типов, для этого
 * необходимо переопределить методы createCustomEditor, setCustomEditorData,
 * saveCustomEditorData, updateCustomEditorTextValue, updateCustomEditorGeometry
 *
 * Возможно одновременное редактирование нескольких объектов.
 * Динамическое добавление объектов, указанных пользователем в перегруженной OnGetNewObject
 * Контроль за удалением объектов, созданных пользователем в перегруженной OnObjectDelete
 * (Если в QVariant размещаются указатели, то пользователь должен сам удалить эти объекты,
 * если там копии объектов, то PropertyBrowser сам удалит все)
 */

class PROPERTYBROWSER_EXPORT PropertyBrowser : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(bool descriptionVisible READ getDescriptionVisible WRITE setDescriptionVisible)
    Q_PROPERTY(bool multiObjectListVisible READ getMultiObjectListVisible WRITE setMultiObjectListVisible)
    Q_PROPERTY(QFont treeFont READ getTreeFont WRITE setTreeFont)
    Q_PROPERTY(QFont listFont READ getListFont WRITE setListFont)
    Q_PROPERTY(QFont descriptionFont READ getDescriptionFont WRITE setDescriptionFont)
    Q_PROPERTY(bool test READ getTest WRITE setTest)

public:
    PropertyBrowser(QWidget *parent = 0);
    ~PropertyBrowser();
    friend class DefaultPropertyItem;
    friend class ObjectVecPropertyItem;

    QVariant getVariant() const;
    void setVariantList(const QVariantList &_valueList);
    QVariantList getVariantList() const;
    void setVariant(const QVariant &_value);

    /*!
     * \brief задает режим отображения окна подробного описания свойства
     */
    void setDescriptionVisible(bool _isVisible);

    /*!
     * \brief получает режим отображение окна подробного описания свойства
     */
    bool getDescriptionVisible() const;

    /*!
     * \brief задает режим отображения списка объектов для редактирования, создания и удаления
     */
    void setMultiObjectListVisible(bool _isVisible);

    /*!
     * \brief получает режим отображение списка объектов для редактирования, создания и удаления
     */
    bool getMultiObjectListVisible() const;

    /*!
     * \brief устанавливает шрифт для окна редактирования свойств объекта
     */
    void setTreeFont(QFont _font);

    /*!
     * \brief получает шрифт окна редактирования свойств объекта
     */
    QFont getTreeFont() const;

    /*!
     * \brief устанавливает шрифт для окна подробного описания свойств
     */
    void setDescriptionFont(QFont _font);

    /*!
     * \brief получает шрифт для окна подробного описания свойств
     */
    QFont getDescriptionFont() const;

    /*!
     * \brief задает шрифт для списка объектов
     */
    void setListFont(QFont _font);

    /*!
     * \brief получает шрифт для списка объектов
     */
    QFont getListFont() const;

    /*!
     * \brief заполнение окна редактирования свойств объекта тестовым классом, для отображения основных редакторов
     * необходим для Дизайнера
     */

    void setTest(bool _test);
    bool getTest();


    /*!
     * \brief возвращает указатель на заданное свойство. если свойство указано неверно, будет возвращен 0
     * \param _propertyName имя свойства, которое нужно получить
     * \return
     */
    AbstractPropertyItem *getProperty(QString _propertyName);

    /*!
     * \brief перевод на лету
     * будет вызвана функция OnGetObjectPropertyInfo у зарегестрированого слушателя, чтобы получить
     * m_propertyInfoMap с переведенными человекопонятными названиями свойств и описания свойств
     */
    void translate();

    /*!
     * \brief проверяет все свойства на правильность заполнения, если установлен флаг isRequried
     * если хотя бы одно свойство заполнено неверно, будет возвращен false, для свойства будет установлен подсвеченный фон
     * и выдан MessageBox с текстом ошибки.
     */
    bool checkTree();

    /*!
     * \brief очищает PropertyBrowser
     */
    void clear();

    /*!
     * \brief установка слушателя для данного класса.
     * необходим для получения QMap<QString, PropertyInfo> описания параметров свойств,
     * при setObject или translate()
     */
    void setListener(PropertyBrowserListener *_listener) {m_listener = _listener;}

    /*!
     * \brief для указанного свойства устанавливает флаг ReadOnly
     */
    void setReadOnly(QString _propertyName, bool _isReadOnly);

    /*!
     * \brief выделяет все объекты в списке
     */
    void selectAllObjects();

    /*!
     * \brief получает значение указанного свойства, если такого свойства не существует,
     * то будет возвращет QVariant()
     */
    QVariant propertyValue(const QString &_propertyName) const;

    /*!
     * \brief задает значени для указанного свойства
     */
    void setPropertyValue(const QString &_propertyName, const QVariant &_value);

    /*!
     * \brief устанавливает тип, который указывается при вызове колбэк функции на создание нового объекта
     */
    void setCreateObjectType(const int _type);

    /*!
     * \brief получает тип, который указывается при вызове колбэк функции на создание нового объекта
     */
    int getCreateObjectType() const;

signals:
    /*!
     * \brief срабатывает при изменение любого свойства
     */
    void propertyValueChanged(QString _propertyName, QVariant _value);

private slots:
    void treeWidgetItemClicked(QTreeWidgetItem *_currentItem, QTreeWidgetItem *_prevItem);
    void listWidgetItemSelectionChanged();
    void valueChanged(QString _propertyName, QVariant _value);

    void addButtonClicked();
    void removeButtonClicked();

private:
    void initListWidget(const QVariantList &_valueList);
    void initVariantList(const QVariantList &_valueList);

    bool m_isTest;
    Ui::PropertyBrowser *ui;
    ItemDelegate *m_delegate;

    PropertyBrowserListener *m_listener;
    QMap<QString, PropertyInfo> m_propertyInfoMap;
    QMap<QString, AbstractPropertyItem*> m_propertyItemMap;
    //QMap<QString, QTreeWidgetItem*> m_topLevelItemsMap;
    QMap<QString, bool> m_expandedState;

    QTreeWidgetItem *m_topLevelItem;

    /*!
     * \brief сохраняет состояние развернутых групп в переменную m_expandedState
     */
    void saveExpandedState();

    /*!
     * \brief загружает состояние развернутых групп из перемнной m_expandedState
     */
    void loadExpandedState();

    /*!
     * \brief убирает подсвечивание фона со всех свойств, установленных с помощью setWarning
     */
    void clearWarnings();

    /*!
     * \brief добавляет новый QTreeWidgetItem в дерево и ассоциирует его с AbstractPropertyItem
     * остальные настройки берутся из PropertyInfo
     */
    static AbstractPropertyItem *addItem(QString _propertyName,
                                         int _propertyType,
                                         bool _isReadOnly,
                                         QTreeWidgetItem *_treeItem,
                                         PropertyInfo _propInfo,
                                         PropertyBrowserListener *_listener = 0);

    static AbstractPropertyItem * createAbstractPropertyItem(QString _propertyName,
                                                             int _propertyType,
                                                             QTreeWidgetItem *item,
                                                             PropertyInfo propInfo,
                                                             PropertyBrowserListener *_listener = 0);

    /*!
     * \brief на основе объектов из _valueList и списка общих свойств из _properties
     * устанавливает значения для редакторов, созданных ранее
     * \param _valueList
     * \param _properties
     */
    void updateProperties(const QVariantList &_valueList, const QStringList &_properties);

    /*!
     * \brief на основе списка свойств все объектов из _valueList создает редакторы для общих свойств
     * \param _valueList
     */
    void createProperties(const QVariantList &_valueList);

    int m_createObjectType;
};
