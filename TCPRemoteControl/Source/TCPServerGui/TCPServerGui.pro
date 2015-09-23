#-------------------------------------------------
#
# Project created by QtCreator 2015-02-11T05:15:13
#
#-------------------------------------------------
#QMAKE_LFLAGS += -static -static-libgcc
QT       += core gui widgets network

include(../../../SingleApplication/Source/singleapplication.pri)

TEMPLATE = app

CONFIG(debug, debug|release) {
    TARGET = TcpServerGui_d
    OBJECTS_DIR = ../TcpServerGui/MOC_OBJ/Debug
    MOC_DIR = ../TcpServerGui/MOC_OBJ/Debug
    DESTDIR = ../!Debug
}
CONFIG(release, debug|release) {
    TARGET = TcpServerGui
    OBJECTS_DIR = ../TcpServerGui/MOC_OBJ/Release
    MOC_DIR = ../TcpServerGui/MOC_OBJ/Release
    DESTDIR = ../!Release
}

SOURCES += main.cpp\
        mainwindow.cpp \
    mytcpserver.cpp \
    winapifunctions.cpp

HEADERS  += mainwindow.h \
    mytcpserver.h \
    protocolpacket.h \
    winapifunctions.h

FORMS    += mainwindow.ui

RESOURCES += \
    res.qrc

LIBS += -lOle32
