#-------------------------------------------------
#
# Project created by QtCreator 2015-09-24T10:53:22
#
#-------------------------------------------------

QT       += core gui widgets

include(../include/PropertyBrowser.pri)

TARGET = PropertyEditor
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h \
    ../include/testobject.h

FORMS    += mainwindow.ui
