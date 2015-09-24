#pragma once

#include <QDataStream>
#include <QStringList>
#include <QVariantMap>

class ExtComboType
{
public:
    ExtComboType(QStringList _valuesList = QStringList(), int _type = -1, QObject *_object = 0) :
        m_valuesList(_valuesList),
        m_type(_type),
        m_object(_object)
    {}

    ExtComboType(const ExtComboType &other)
    {
        m_valuesList    = other.m_valuesList;
        m_type          = other.m_type;
        m_object        = other.m_object;
    }

    ExtComboType const & operator = (const ExtComboType & other)
    {
        m_valuesList    = other.m_valuesList;
        m_type          = other.m_type;
        m_object        = other.m_object;
        return *this;
    }

    friend QDataStream &operator<<(QDataStream &out, const ExtComboType &myObj)
    {
        QVariantMap m;
        m.insert("m_valuesList",    myObj.m_valuesList);
        m.insert("m_type",          myObj.m_type);
        out << m;
        return out;
    }

    friend QDataStream &operator>>(QDataStream &in, ExtComboType &myObj)
    {
        QVariantMap m;
        in >> m;
        myObj.m_valuesList  = m.value("m_valuesList").toStringList();
        myObj.m_type        = m.value("m_type").toInt();
        return in;
    }

    QStringList m_valuesList;
    int         m_type;
    QObject     *m_object;
};

Q_DECLARE_METATYPE(ExtComboType)

namespace PropertyType
{
static int ExtComboTypeId()
{
    return qMetaTypeId<ExtComboType>();
}
}

