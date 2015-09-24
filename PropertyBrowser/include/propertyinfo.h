#pragma once
#include <QString>
#include <QMap>
#include <QVariant>

/*!
 * \brief The PropertyInfo class
 * Класс используется для настройки поведения свойств,
 * которые будут отображаться в PropertyBrowser
 * Для задания его в PropertyBrowser необходимо использовать QMap<QString, PropertyInfo>
 * Где QString - имя свойства, PropertyInfo соответсвенно его описание
 * Так что можно в описание нужного класса добавить метод static QMap<QString, PropertyInfo> getPropInfo();
 */

class PropertyInfo
{
public:
    PropertyInfo(  QString _propertyCaption = "",
                   QString _group = "",
                   QString _description = "",
                   bool _isHidden = false,
                   bool _isRequried = false,
                   bool _isExpandable = false,
                   QMap<int, QVariant> _properies = QMap<int, QVariant>()):
        m_caption(_propertyCaption),
        m_group(_group),
        m_isHidden(_isHidden),
        m_isRequried(_isRequried),
        m_description(_description),
        m_isExpandable(_isExpandable),
        m_properties(_properies)
    { }

    QString m_description;  ///<текст, который будет отображаться в окне описания свойства объекта
    QString m_group;        ///<название группы к которой будет принадлежать свойство
    QString m_caption;      ///<человекопонятное название свойства, которое будет отображено в первой колонке PropertyBrowser
    bool m_isHidden;        ///<будет ли свойство отображено в PropertyBrowser
    bool m_isRequried;      ///<является ли свойство обязательным для заполнения
    bool m_isExpandable;
    QMap<int, QVariant> m_properties;   ///<свойства индивидуальные для каждого редактора
};

typedef QMap<QString, PropertyInfo> PropertyInfoMapType;
Q_DECLARE_METATYPE(PropertyInfoMapType)
Q_DECLARE_METATYPE(QObject*)

namespace PropertyType
{
static int PropertyInfoMapTypeId()
{
    return qMetaTypeId<PropertyInfoMapType>();
}

static int pObjectType()
{
    return qMetaTypeId<QObject*>();
}
}
