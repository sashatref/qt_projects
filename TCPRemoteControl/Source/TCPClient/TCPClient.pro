#-------------------------------------------------
#
# Project created by QtCreator 2015-02-11T16:49:11
#
#-------------------------------------------------
QMAKE_LFLAGS += -static -static-libgcc
QT       += core gui network widgets

TEMPLATE = app

include(../TcpServerGui/TcpServerGui.pri)

CONFIG(debug, debug|release) {
    TARGET = TCPClient_d
    OBJECTS_DIR = ../TCPClient/MOC_OBJ/Debug
    MOC_DIR = ../TCPClient/MOC_OBJ/Debug
    DESTDIR = ../!Debug
}
CONFIG(release, debug|release) {
    TARGET = TCPClient
    OBJECTS_DIR = ../TCPClient/MOC_OBJ/Release
    MOC_DIR = ../TCPClient/MOC_OBJ/Release
    DESTDIR = ../!Release
}


SOURCES += main.cpp\
        mainwindow.cpp \
    remotecontrol.cpp

HEADERS  += mainwindow.h \
    remotecontrol.h

FORMS    += mainwindow.ui

CONFIG += mobility
MOBILITY = 

RESOURCES += \
    images.qrc

