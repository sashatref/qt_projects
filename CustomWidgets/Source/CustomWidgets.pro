QT          += widgets

INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

TEMPLATE    = lib

#DEFINES += STATIC

#названия файлов для сборки статической библиотеки
contains(DEFINES, STATIC) {
    CONFIG += staticlib
    CONFIG(debug, debug|release) {
        TARGET = ../CustomWidgets_static_vc10_d
    }
    CONFIG(release, debug|release) {
        TARGET = ../CustomWidgets_static_vc10
    }
} else {
#названия файлов для сборки динамической библиотеки
    DEFINES += CUSTOM_WIDGETS_PLUGIN
    CONFIG(debug, debug|release) {
        TARGET = ../CustomWidgets_vc10_d
    }
    CONFIG(release, debug|release) {
        TARGET = ../CustomWidgets_vc10
    }
}


HEADERS     = \
    MyTableView/mytableview.h \
    ExtendedTableView/extendedtableview.h \
    RichLabel/richlabel.h \
    ExtComboEdit/extcomboedit.h \
    ExtComboEdit/extcombotype.h \
    ChooseList/chooselist.h \
    SmartListWidget/smartlist.h \
    ExtendedTableView/intitem.h \
    ExtendedTableView/dateitem.h \
    ExtendedTableView/datetimeitem.h \
    ChooseList/customlistwidgetitem.h \
    ExtendedTableView/filterwidget.h \
    CustomWidgets_pch.h \

SOURCES     = \
    ChooseList/chooselist.cpp \
    ExtComboEdit/extcomboedit.cpp \
    SmartListWidget/smartlist.cpp \
    RichLabel/richlabel.cpp \
    MyTableView/mytableview.cpp \
    ExtendedTableView/filterwidget.cpp \
    ExtendedTableView/extendedtableview.cpp

#этот файлы подключаются только при сборке динамической библиотеки, которую можно использовать для дизайнера
contains(DEFINES, CUSTOM_WIDGETS_PLUGIN) {
    win32:RC_FILE += customwidgets.rc
    QT  += designer

    HEADERS     += \
        ChooseList/chooselistplugin.h \
        ExtendedTableView/extendedtableviewplugin.h \
        MyTableView/mytableviewplugin.h \
        RichLabel/richlabelplugin.h \
        SmartListWidget/smartlistwidgetplugin.h \
        plugincollection.h

    SOURCES     += \
        ChooseList/chooselistplugin.cpp \
        ExtendedTableView/extendedtableviewplugin.cpp \
        MyTableView/mytableviewplugin.cpp \
        RichLabel/richlabelplugin.cpp \
        SmartListWidget/smartlistwidgetplugin.cpp \
        plugincollection.cpp
}

RESOURCES += \
    CustomWidgets_images.qrc \
    CustomWidgets_translate.qrc

FORMS += \
    ChooseList/chooselist.ui \
    SmartListWidget/smartlist.ui \
    ExtendedTableView/extendedtableview.ui \
    ExtendedTableView/filterwidget.ui

DISTFILES += \
    CustomWidgetsPlugin.pri

TRANSLATIONS    = translate/ru.ts translate/en.ts

#секция необходия для автоинкрементирования версии сборки
build_nr.commands = $$PWD/VersionAutoIncrement.exe $$PWD/buildNumber.h
build_nr.depends = FORCE
QMAKE_EXTRA_TARGETS += build_nr
PRE_TARGETDEPS += build_nr
