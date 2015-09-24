#pragma once

#include <QString>
#include <QVariantMap>

namespace PropertyType
{
    static int FileTypeId();
}

class FileType
{
public:
    FileType(QString _path = "", QByteArray _file = QByteArray()):
        m_path(_path),
        m_file(_file)
    {
        registerType();
    }

    FileType(const FileType &other):
        m_path(other.m_path),
        m_file(other.m_file)
    {}

    bool operator < (const FileType &other) const
    {
        return m_path < other.m_path;
    }

    bool operator ==(const FileType &other) const
    {
        return m_path == other.m_path;
    }

    friend QDataStream &operator<<(QDataStream &out, const FileType &myObj)
    {
        QVariantMap m;
        m.insert("m_path", myObj.m_path);

        out << m;
        return out;
    }

    friend QDataStream &operator>>(QDataStream &in, FileType &myObj)
    {
        QVariantMap m;
        in >> m;

        myObj.m_path = m.value("m_path").toString();

        return in;
    }

    static QString toString(const FileType &_value)
    {
        return _value.m_path;
    }

    static void registerType()
    {
        if(!QMetaType::hasRegisteredComparators(PropertyType::FileTypeId()))
        {
            QMetaType::registerComparators<FileType>();
        }
        if(!QMetaType::hasRegisteredConverterFunction(PropertyType::FileTypeId(), QVariant::String))
        {
            QMetaType::registerConverter<FileType, QString>(&FileType::toString);
        }

        qRegisterMetaTypeStreamOperators<FileType>("FileType");
    }

    QString m_path;
    QByteArray m_file;
};

Q_DECLARE_METATYPE(FileType)

namespace PropertyType
{
static int FileTypeId()
{
    return qMetaTypeId<FileType>();
}
}
