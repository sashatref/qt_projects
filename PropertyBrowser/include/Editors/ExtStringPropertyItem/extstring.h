#pragma once

#include <QObject>
#include <QVariantMap>

namespace PropertyType
{
    static int ExtStringTypeId();
}

class ExtString
{
public:
    ExtString(QString _text = "") : m_text(_text)
    {
        registerType();
    }
    ExtString(const char* _text) : m_text(_text)
    {
        registerType();
    }
    ExtString(const ExtString &other)
    {
        m_text = other.m_text;
    }

    ExtString const &operator = (const ExtString & other)
    {
        m_text = other.m_text;
        return *this;
    }

    bool operator <(const ExtString &other) const
    {
        return m_text < other.m_text;
    }

    bool operator ==(const ExtString &other) const
    {
        return m_text == other.m_text;
    }

    friend QDataStream &operator<<(QDataStream &out, const ExtString &myObj)
    {
        QVariantMap m;
        m.insert("m_text", myObj.m_text);

        out << m;
        return out;
    }

    friend QDataStream &operator>>(QDataStream &in, ExtString &myObj)
    {
        QVariantMap m;
        in >> m;

        myObj.m_text = m.value("m_text").toString();

        return in;
    }

    static QString toString(const ExtString &_value)
    {
        QString result = _value.m_text;
        while(result.contains("\n"))
        {
            result = result.replace("\n","");
        }
        return result;
    }

    static void registerType()
    {
        if(!QMetaType::hasRegisteredComparators(PropertyType::ExtStringTypeId()))
        {
            QMetaType::registerComparators<ExtString>();
        }
        if(!QMetaType::hasRegisteredConverterFunction(PropertyType::ExtStringTypeId(), QVariant::String))
        {
            QMetaType::registerConverter<ExtString, QString>(&ExtString::toString);
        }

        qRegisterMetaTypeStreamOperators<ExtString>("ExtString");
    }

    QString m_text;
};

Q_DECLARE_METATYPE(ExtString)

namespace PropertyType
{
    static int ExtStringTypeId()
    {
        return qMetaTypeId<ExtString>();
    }
}
