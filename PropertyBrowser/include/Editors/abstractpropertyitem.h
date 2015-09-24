#pragma once

#include <QString>
#include <QWidget>
#include <QVariant>
#include <QTreeWidgetItem>

/*!
 * \brief The AbstractPropertyItem class
 * базовый класс, который используется для описания свойств объектов в PropertyBrowser
 */

class AbstractPropertyItem : public QObject
{
    Q_OBJECT
public:
    AbstractPropertyItem(QString _propertyName, QString _propertyCaption, int _propertyType, QTreeWidgetItem *_item);
    virtual ~AbstractPropertyItem() {}

    /*!
     * \brief устанавливает для свойства флаг Warning
     * задает QTreeWidgetItem красный фон, чтоб привлечь внимание пользователя
     */
    void setWarning(bool _isWarning);

    /*!
     * \brief получает значние флага Warning
     */
    bool getWarning() const;

    /*!
     * \brief получает имя свойства
     */
    QString getPropertyName() const;

    /*!
     * \brief получает человекопонятное название свойства, которое отображается в 1 колонке PropertyBrowser
     */
    QString getPropertyCaption() const;

    /*!
     * \brief устанавливает человекопонятное название свойства, которое отображается в 1 колонке PropertyBrowser
     * необходимо при смене языка программы "на лету"
     */
    void setPropertyCaption(QString _caption);

    /*!
     * \brief возвращает тип свойства, который задается в конструкторе
     */
    int getPropertyType() const;

    /*!
     * \brief получает значение флага, отображается ли свойство
     * (пока не ясно нужно ли оно)
     */
    bool getVisible() const;

    /*!
     * \brief получает значение флага, является ли свойство обязательным для заполнения
     */
    bool getRequried() const;

    /*!
     * \brief получает подробное человекопонятное описание для свойства
     */
    QString getDescription() const;

    /*!
     * \brief получает название группы, к которой принадлежит свойство
     */
    QString getGroup() const;

    /*!
     * \brief устанавливает название группы в которую будет добавлено свойство
     * необходимо при смене языка программы "на лету"
     */
    void setGroup(QString _group);

    /*!
     * \brief устанавливает флаг readonly
     * если readonly == true, то редактор не будет вызываться.
     */
    void setReadOnly(bool _isReadOnly);

    /*!
     * \brief возвращает флаг readonly
     */
    bool getReadOnly() const;

    /*!
     * \brief устанавливает подробное человекопонятно описание для свойства
     * необходимо при смене языка программы "на лету"
     */
    void setDescription(QString _description);

    /*!
     * \brief устанавливает значение флага, является ли свойство обязательным для заполнения
     */
    void setRequried(bool _isRequeried);

    /*!
     * \brief устанавливает значение флага, отображается ли свойство
     * (пока не ясно нужно ли оно)
     */
    void setVisible(bool _isVisible);

    /*!
     * \brief устанавливает значение для свойства
     */
    void setValue(QVariant _value);

    /*!
     * \brief получает значение для свойства
     */
    QVariant getValue() const;

    /*!
     * \brief устанавливает ранеесозданнй QTreeWidgetItem, который соответствует данному свойству
     */
    void setTreeItem(QTreeWidgetItem *_item);

    void initEmptyEditor();

    /*!
     * \brief получает QTreeWidgetItem закрепленный за этим свойством
     */
    QTreeWidgetItem *getTreeItem() const;

    /*!
     * \brief в данной функции необходимо создать и настроить редактор,
     *  который будет отображаться для редактирования значения свойства
     * \param _widget родительский виджет, в данном случае это QTreeWidget
     * \return редактор, который будет создаваться по переходу к данному свойству
     */

    virtual QWidget* createEditor(QWidget *_parent) = 0;

    /*!
     * \brief в данной функции небходимо редактор проинициализировать данными из m_value;
     * \param _widget указатель на редактор созданный в методе createEditor
     */
    virtual void setEditorData(QWidget *_widget) = 0;

    /*!
     * \brief в данной функции необходимо сохранить данные из редактора _widget в m_value, используя setValue
     * \param _widget указатель на редактор созданный в методе createEditor
     */
    virtual void saveEditorData(QWidget *_widget) = 0;

    /*!
     * \brief в данной функции можно изменить геометрию редактора, если это необходимо
     * перед вызовом этой функции уже выполнено _widget->setGeometry(_option.rect);
     * \param _widget указатель на редактор созданный в методе createEditor
     * \param _option редомендуемые размеры
     */
    virtual void updateGeometry(QWidget *_widget, const QStyleOptionViewItem _option) { &_widget; &_option;}

    /*!
     * \brief в данной функции необходимо на основание значения m_value установить текст для неактивного редактора
     * \code
     *      m_treeItem->setText(1, getValue().toString());
     * \endcode
     */
    virtual void updateTextValue();

    /*!
     * \brief метод выполняется, при выполнение checkTree() для PropertyBrowser.
     * в данной функции нужно проверить, установлен ли флаг isRequried, если да
     * то проверить, корректно ли заполнены данные в редакторе.
     * Если будет возвращет false то выполнение функции checkTree() будет тоже остановлено,
     * данное поле свойства будет подсвечено функцией setWarning(true) и выдано текстовое сообщение об ошибке,
     * возвращаеммое методом getCheckErrorMessage()
     * \code
     *      if(getRequried() && getValue().toString().isEmpty())
     *      {
     *          return false;
     *      }
     *      return true;
     * \endcode
     * \return
     */
    virtual bool checkItem() {return true;}

    /*!
     * \brief метод выполняеться, если функция checkItem() вернула false
     * должен возвращать подробное описание ошибки:
     * "Не заполнено поле 'Имя'" или "Не выбран элемент из списка для поля 'Школа'"
     * в тексте ошибки обязательно указать имя свойства, чтобы пользователю было понятенее в чем проблема
     * \return
     */
    virtual QString getCheckErrorMessage() {return QString("Property %1 check error").arg(getPropertyCaption());}

    /*!
     * \brief устанавливает свойства индивидуальные для каждого редактора
     * \param _id ID необходимого свойства
     * \param _value значение необходимого свойства
     */
    void setProperty(int _id, QVariant _value) { m_propertiesMap[_id] = _value;}

    /*!
     * \brief получает свойство индивидуальное для каждого редактора
     * \param _id ID необходимого свойства
     * \return значение необходимого свойства
     */
    QVariant getProperty(int _id) {return m_propertiesMap[_id];}

    /*!
     * \brief к существующим свойства добавляет указанные,
     * если ключи совпадают - то перезаписывает
     */
    void appendProperties(QMap<int, QVariant> _properties);

    void setExpandable(bool _isExpandable);

signals:
    /*!
     * \brief сигнал срабатывает при изменение значения m_value
     * PropertyBrowser подписывается на данный сигнал всех свойств и испускает общий для всех сигнал
     * \param _propertyName имя свойства
     * \param _value        значение свойства
     */
    void valueChanged(QString _propertyName, QVariant _value);

protected:
    QTreeWidgetItem *m_treeItem;
    QMap<int, QVariant> m_propertiesMap;
    bool m_isExpandable;

private:
    QString m_propertyName;
    QString m_propertyCaption;
    QString m_group;
    QString m_description;
    bool m_isVisible;
    bool m_isWarning;
    bool m_isRequried;
    bool m_isReadOnly;
    int m_propertyType;
    QVariant m_value;
};
