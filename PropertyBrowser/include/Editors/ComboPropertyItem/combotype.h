#pragma once

#include <QObject>
#include <QDataStream>
#include <QVariantMap>

namespace PropertyType
{
    static int ComboTypeId();
}

class ComboType
{
public:
    ComboType(const ComboType &other)
    {
        m_valuesList    = other.m_valuesList;
        m_currentValue  = other.m_currentValue;
        m_index         = other.m_index;
    }

    ComboType(QStringList values = QStringList(), QString currentValue = "")
    {
        ComboType::registerType();
        m_valuesList    = values;
        m_currentValue  = currentValue;
        m_index         = -1;
    }

    ComboType const & operator = (const ComboType & other)
    {
        m_valuesList    = other.m_valuesList;
        m_currentValue  = other.m_currentValue;
        m_index         = other.m_index;
        return *this;
    }

    bool operator ==(const ComboType &other) const
    {
        return m_currentValue == other.m_currentValue;
    }

    bool operator <(const ComboType &other) const
    {
        return m_currentValue < other.m_currentValue;
    }

    friend QDataStream &operator<<(QDataStream &out, const ComboType &myObj)
    {
        QVariantMap m;
        m.insert("m_currentValue", myObj.m_currentValue);
        m.insert("m_valuesList", myObj.m_valuesList);
        m.insert("m_index", myObj.m_index);

        out << m;
        return out;
    }

    friend QDataStream &operator>>(QDataStream &in, ComboType &myObj)
    {
        QVariantMap m;
        in >> m;

        myObj.m_currentValue = m.value("m_currentValue").toString();
        myObj.m_valuesList = m.value("m_valuesList").toStringList();
        myObj.m_index = m.value("m_index").toInt();

        return in;
    }

    static QString toString(const ComboType &_value)
    {
        return _value.m_currentValue;
    }

    static void registerType()
    {
        if(!QMetaType::hasRegisteredComparators(PropertyType::ComboTypeId()))
        {
            QMetaType::registerComparators<ComboType>();
        }
        if(!QMetaType::hasRegisteredConverterFunction(PropertyType::ComboTypeId(), QVariant::String))
        {
            QMetaType::registerConverter<ComboType, QString>(&ComboType::toString);
        }

        qRegisterMetaTypeStreamOperators<ComboType>("ComboType");
    }

    QStringList m_valuesList;
    QString     m_currentValue;
    int         m_index;
};

Q_DECLARE_METATYPE(ComboType)

namespace PropertyType
{
    static int ComboTypeId()
    {
        return qMetaTypeId<ComboType>();
    }
}
