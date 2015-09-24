#pragma once

#include <QObject>
#include "setgetMacro.h"
#include "Editors/ComboPropertyItem/combotype.h"
#include "Editors/ExtStringPropertyItem/extstring.h"
#include "Editors/FlagsPropertyItem/flagstype.h"
#include "Editors/editorproperties.h"
#include "Editors/FilePropertyItem/filetype.h"
#include "Editors/editorproperties.h"
#include "propertyinfo.h"

#include <QDate>
#include <QDateTime>
#include <QFont>
#include <QVector>

namespace PropertyType
{
static int TestObjectId();
static int MyClassId();
}

class MyClass : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int intValue READ field1 WRITE setField1)
    Q_PROPERTY(QString field2 READ field2 WRITE setField2)
    Q_PROPERTY(double field3 READ field3 WRITE setField3)
public:
    setget(int, field1, setField1, m_field1)
    setget(QString, field2, setField2, m_field2)
    setget(double, field3, setField3, m_field3)

    MyClass()
    {
        registerType();
        m_field1 = 10;
        m_field2 = "hello";
        m_field3 = 5.6;
    }

    MyClass(const MyClass &other)
    {
        m_field1 = other.m_field1;
        m_field2 = other.m_field2;
        m_field3 = other.m_field3;
    }

    MyClass &operator=(const MyClass &other)
    {
        m_field1 = other.m_field1;
        m_field2 = other.m_field2;
        m_field3 = other.m_field3;
        return *this;
    }

    static QObject* toObject(const MyClass &_object)
    {
        return const_cast<MyClass*>(&_object);
    }

    static PropertyInfoMapType toPropertyMap(const MyClass &)
    {
        PropertyInfoMapType m;
        m.insert("intValue", PropertyInfo("Field 1", "", "Descr1", false, false, false));
        m.insert("field2", PropertyInfo("Field 2", "", "Descr2", false, false, false));
        m.insert("field3", PropertyInfo("Field 3", "", "Descr3", false, false, false));
        return m;
    }

    static void registerType()
    {
        if(!QMetaType::hasRegisteredConverterFunction(PropertyType::MyClassId(), PropertyType::pObjectType()))
        {
            QMetaType::registerConverter<MyClass, QObject*>(&MyClass::toObject);
        }
        if(!QMetaType::hasRegisteredConverterFunction(PropertyType::MyClassId(), PropertyType::PropertyInfoMapTypeId()))
        {
             QMetaType::registerConverter<MyClass, PropertyInfoMapType>(&MyClass::toPropertyMap);
        }

        qRegisterMetaTypeStreamOperators<MyClass>("MyClass");
    }

    friend QDataStream &operator<<(QDataStream &out, const MyClass &myObj)
    {
        QVariantMap m;
        m.insert("m_field1",    myObj.m_field1);
        m.insert("m_field2",    myObj.m_field2);
        m.insert("m_field3",    myObj.m_field3);
        out << m;
        return out;
    }

    friend QDataStream &operator>>(QDataStream &in, MyClass &myObj)
    {
        QVariantMap m;
        in >> m;

        myObj.m_field1  = m.value("m_field1").toInt();
        myObj.m_field2  = m.value("m_field2").toString();
        myObj.m_field3  = m.value("m_field3").toDouble();

        return in;
    }

private:
    int m_field1;
    QString m_field2;
    double m_field3;
};

Q_DECLARE_METATYPE(MyClass)

namespace PropertyType
{
static int MyClassId()
{
    return qMetaTypeId<MyClass>();
}
}

class TestObject : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int intValue READ intValue WRITE setIntValue)
    Q_PROPERTY(bool boolValue READ boolValue WRITE setBoolValue)
    Q_PROPERTY(ExtString extStringValue READ extStringValue WRITE setExtStringValue)
    Q_PROPERTY(double doubleValue READ doubleValue WRITE setDoubleValue)
    Q_PROPERTY(QString stringValue READ stringValue WRITE setStringValue)
    Q_PROPERTY(FlagsType flagsValue READ flagsValue WRITE setFlagsValue)
    Q_PROPERTY(QDate dateValue READ dateValue WRITE setDateValue)
    Q_PROPERTY(FileType fileEditValue READ fileEditValue WRITE setFileEditValue)
    Q_PROPERTY(QDateTime dateTimeValue READ dateTimeValue WRITE setDateTimeValue)
    Q_PROPERTY(ComboType comboValue READ comboValue WRITE setComboValue)
    Q_PROPERTY(QFont fontValue READ fontValue WRITE setFontValue)
    Q_PROPERTY(QVector<QVariant> vec READ vec WRITE setVec)
    Q_PROPERTY(QStringList stringListValue READ stringListValue WRITE setStringListValue)
    Q_PROPERTY(MyClass myClass READ myClassValue WRITE setMyClassValue)

public:
    TestObject(QObject *parent = 0) :
        QObject(parent),
        intVal(20),
        doubleVal(5.4),
        stringVal("value"),
        extStringVal("haha"),
        dateVal(QDate(2000,5,9)),
        dateTimeVal(QDateTime(QDate(1995,6,10), QTime(22,12,32))),
        comboVal(ComboType(QStringList() << "value2" << "value1" << "value3", "value2")),
        fontVal(QFont())
    {
        registerType();

        fileEditVal = FileType("C:/file.txt");
        fileEditVal.m_file = QByteArray("dasdasdasdasdas");
        //lineEditVal = ExtLineType();

        flagsVal.m_valuesList = QStringList() << "flag1" << "falg2" << "falg3" << "flag4";
        flagsVal.m_currentInt = QVector<int>() << 1 << 3;
    }

    setget(int, intValue, setIntValue, intVal)
    setget(bool, boolValue, setBoolValue, boolVal)
    setget(ExtString, extStringValue, setExtStringValue, extStringVal)
    setget(double, doubleValue, setDoubleValue, doubleVal)
    setget(QString, stringValue, setStringValue, stringVal)
    setget(QDate, dateValue, setDateValue, dateVal)
    setget(QDateTime, dateTimeValue, setDateTimeValue, dateTimeVal)
    setget(FileType, fileEditValue, setFileEditValue, fileEditVal)
    setget(ComboType, comboValue, setComboValue, comboVal)
    setget(FlagsType, flagsValue, setFlagsValue, flagsVal)
    setget(QFont, fontValue, setFontValue, fontVal)
    setget(QStringList, stringListValue, setStringListValue, stringListVal)
    setget(MyClass, myClassValue, setMyClassValue, myClassVal)

    void setVec(QVector<QVariant> values)
    {
        linkStringVal.clear();

        for(int i = 0; i < values.size(); i++)
        {
            linkStringVal.append(values[i].value<MyClass>());
        }
    }
    QVector<QVariant> vec()
    {
        QVector<QVariant> values;

        for(int i = 0; i < linkStringVal.size(); i++)
        {
            values.append(QVariant::fromValue(linkStringVal.at(i)));
        }

        return values;
    }

    TestObject(const TestObject &other)
    {
        intVal    = other.intVal;
        boolVal = other.boolVal;
        extStringVal = other.extStringVal;
        doubleVal =   other.doubleVal;
        stringVal = other.stringVal;
        dateVal     = other.dateVal;
        dateTimeVal = other.dateTimeVal;
        fileEditVal = other.fileEditVal;
        comboVal = other.comboVal;
        flagsVal = other.flagsVal;
        fontVal = other.fontVal;
        linkStringVal = other.linkStringVal;
        stringListVal = other.stringListVal;
        myClassVal = other.myClassVal;
    }

    const TestObject &operator =(const TestObject &other)
    {
        intVal    = other.intVal;
        boolVal = other.boolVal;
        extStringVal = other.extStringVal;
        doubleVal = other.doubleVal;
        stringVal = other.stringVal;
        dateVal     = other.dateVal;
        dateTimeVal = other.dateTimeVal;
        fileEditVal = other.fileEditVal;
        comboVal = other.comboVal;
        flagsVal = other.flagsVal;
        fontVal = other.fontVal;
        linkStringVal = other.linkStringVal;
        stringListVal = other.stringListVal;
        myClassVal = other.myClassVal;
        return *this;
    }

    static QObject* tostaticObject(const TestObject &_value)
    {
        TestObject *object = const_cast<TestObject*>(&_value);
        return object;
    }

    static PropertyInfoMapType toPropertyMap(const TestObject&)
    {
        QMap<QString, PropertyInfo> m;
        m.insert("intValue", PropertyInfo("Int value", "", "Int value description", false, false, false));
        m.insert("boolValue", PropertyInfo("Bool value", "", "Bool value description", false, false, false));
        m.insert("stringValue", PropertyInfo("String value", "", "String value description", false, false, false));
        m.insert("extStringValue", PropertyInfo("ExtString value", "", "String value description", false, false, false));
        m.insert("doubleValue", PropertyInfo("Double value", "", "String value description", false, false, false));
        m.insert("dateValue", PropertyInfo("Date  value", "", "String value description", false, false, false));
        m.insert("dateTimeValue", PropertyInfo("Date time value", "", "String value description", false, false, false));
        m.insert("fileEditValue", PropertyInfo("File  value", "", "String value description", false, false, false));
        m.insert("comboValue", PropertyInfo("Combo value", "", "String value description", false, false, false));
        m.insert("flagsValue", PropertyInfo("Flags value", "", "String value description", false, false, false));
        m.insert("fontValue", PropertyInfo("Font value", "", "String value description", false, false, false));
        m.insert("stringListValue", PropertyInfo("StringList value", "", "String value description", false, false, false));
        m.insert("vec", PropertyInfo("Vector value", "", "String value description", false, false, false));
        m.insert("myClass", PropertyInfo("MyClass", "", "String value description", false, false, true));
        m["vec"].m_properties[ObjectVecProperty::CreateObjectType] = PropertyType::MyClassId();
        return m;
    }

    static void registerType()
    {
        if(!QMetaType::hasRegisteredConverterFunction(PropertyType::TestObjectId(), PropertyType::PropertyInfoMapTypeId()))
        {
            QMetaType::registerConverter<TestObject, PropertyInfoMapType>(&TestObject::toPropertyMap);
        }
        if(!QMetaType::hasRegisteredConverterFunction(PropertyType::TestObjectId(), PropertyType::pObjectType()))
        {
            QMetaType::registerConverter<TestObject, QObject*>(&TestObject::tostaticObject);
        }

        qRegisterMetaTypeStreamOperators<TestObject>("TestObject");
        qRegisterMetaTypeStreamOperators<QVector<MyClass>>("QVector<MyClass>");
    }

    friend QDataStream &operator<<(QDataStream &out, const TestObject &myObj)
    {
        QVariantMap m;
        m.insert("intVal",          myObj.intVal);
        m.insert("doubleVal",    myObj.doubleVal);
        m.insert("boolVal",    myObj.boolVal);
        m.insert("stringVal",    myObj.stringVal);
        m.insert("extStringVal",    QVariant::fromValue(myObj.extStringVal));
        m.insert("dateVal",    myObj.dateVal);
        m.insert("dateTimeVal",    QVariant::fromValue(myObj.dateTimeVal));
        m.insert("fileEditVal",    QVariant::fromValue(myObj.fileEditVal));
        m.insert("comboVal",    QVariant::fromValue(myObj.comboVal));
        m.insert("flagsVal",    QVariant::fromValue(myObj.flagsVal));
        m.insert("fontVal",    QVariant::fromValue(myObj.fontVal));
        m.insert("linkStringVal",    QVariant::fromValue(myObj.linkStringVal));
        m.insert("stringListVal",    QVariant::fromValue(myObj.stringListVal));
        m.insert("myClassVal",    QVariant::fromValue(myObj.myClassVal));
        out << m;
        return out;
    }

    friend QDataStream &operator>>(QDataStream &in, TestObject &myObj)
    {
        QVariantMap m;
        in >> m;

        myObj.intVal  = m.value("intVal").toInt();
        myObj.doubleVal  = m.value("doubleVal").toDouble();
        myObj.boolVal  = m.value("boolVal").toBool();
        myObj.stringVal  = m.value("stringVal").toString();
        myObj.extStringVal  = m.value("extStringVal").value<ExtString>();
        myObj.dateVal  = m.value("dateVal").toDate();
        myObj.dateTimeVal  = m.value("dateTimeVal").toDateTime();
        myObj.fileEditVal  = m.value("fileEditVal").value<FileType>();
        myObj.comboVal  = m.value("comboVal").value<ComboType>();
        myObj.flagsVal  = m.value("flagsVal").value<FlagsType>();
        myObj.fontVal  = m.value("fontVal").value<QFont>();
        myObj.linkStringVal  = m.value("linkStringVal").value<QVector<MyClass>>();
        myObj.stringListVal  = m.value("stringListVal").toStringList();
        myObj.myClassVal  = m.value("myClassVal").value<MyClass>();

        return in;
    }

    int intVal;
    double doubleVal;
    bool boolVal;
    QString stringVal;
    ExtString extStringVal;
    QDate dateVal;
    QDateTime dateTimeVal;
    FileType fileEditVal;
    ComboType comboVal;
    FlagsType flagsVal;
    QFont fontVal;
    QVector<MyClass> linkStringVal;
    QStringList stringListVal;
    MyClass myClassVal;
};

Q_DECLARE_METATYPE(TestObject)

namespace PropertyType
{
static int TestObjectId()
{
    return qMetaTypeId<TestObject>();
}
}
