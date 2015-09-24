#pragma once

Q_DECLARE_METATYPE(QVector<QVariant>)

namespace PropertyType
{
    static int ObjectVecTypeId()
    {
        return qMetaTypeId<QVector<QVariant>>();
    }
}

namespace ObjectVec {
static QString toString(const QVector<QVariant> &_value){
    return QObject::tr("Items: ") + QString::number(_value.size());
}
}
