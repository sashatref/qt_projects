#pragma once

#include <QObject>
#include <QVector>
#include <QStringList>
#include <QVariantMap>

namespace PropertyType
{
    static int FlagsTypeId();
}

class FlagsType
{
public:
    FlagsType(QStringList _valuesList = QStringList(),
              QVector<int> _currentValues = QVector<int>(),
              QVector<int> _currentInt = QVector<int>()) :
        m_valuesList(_valuesList),
        m_currentValue(_currentValues),
        m_currentInt(_currentInt)
    {
        FlagsType::registerType();
    }

    FlagsType(const FlagsType &other)
    {
        m_valuesList    = other.m_valuesList;
        m_currentValue  = other.m_currentValue;
        m_currentInt    = other.m_currentInt;
    }

    FlagsType const & operator = (const FlagsType & other)
    {
        m_valuesList    = other.m_valuesList;
        m_currentValue  = other.m_currentValue;
        m_currentInt    = other.m_currentInt;
        return *this;
    }

    bool operator < (const FlagsType &other) const
    {
        return m_currentValue.size() < other.m_currentValue.size();
    }

    bool operator ==(const FlagsType &other) const
    {
        return m_currentValue == other.m_currentValue;
    }

    friend QDataStream &operator<<(QDataStream &out, const FlagsType &myObj)
    {
        QVariantMap m;
        m.insert("m_currentValue", QVariant::fromValue(myObj.m_currentValue));
        m.insert("m_valuesList", QVariant::fromValue(myObj.m_valuesList));
        m.insert("m_currentInt", QVariant::fromValue(myObj.m_currentInt));

        out << m;
        return out;
    }

    friend QDataStream &operator>>(QDataStream &in, FlagsType &myObj)
    {
        QVariantMap m;
        in >> m;
        myObj.m_currentValue = m.value("m_currentValue").value<QVector<int> >();
        myObj.m_valuesList = m.value("m_valuesList").toStringList();
        myObj.m_currentInt = m.value("m_currentInt").value<QVector<int> >();

        return in;
    }

    static QString toString(const FlagsType &_value)
    {
        QString text = "";
        for(int i = 0; i < _value.m_currentValue.count(); i++)
        {
            text += _value.m_valuesList.at(_value.m_currentValue[i]) + "|";
        }
        text = text.left(text.lastIndexOf("|"));
        return text;
    }

    static void registerType()
    {
        if(!QMetaType::hasRegisteredComparators(PropertyType::FlagsTypeId()))
        {
            QMetaType::registerComparators<FlagsType>();
        }

        if(!QMetaType::hasRegisteredConverterFunction(PropertyType::FlagsTypeId(), QVariant::String))
        {
            QMetaType::registerConverter<FlagsType, QString>(&FlagsType::toString);
        }

        qRegisterMetaTypeStreamOperators<FlagsType>("FlagsType");
        qRegisterMetaTypeStreamOperators<QVector<int> >("QVector<int>");
    }

    QStringList     m_valuesList;
    QVector<int>    m_currentValue;
    QVector<int>    m_currentInt;
};

Q_DECLARE_METATYPE(FlagsType)

namespace PropertyType
{
static int FlagsTypeId()
{
    return qMetaTypeId<FlagsType>();
}
}
