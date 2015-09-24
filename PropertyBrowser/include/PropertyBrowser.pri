INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

CONFIG(debug, debug|release) {
    LIBS += $$PWD/../lib/PropertyBrowser_vc10_d.lib
}
CONFIG(release, debug|release) {
    LIBS += $$PWD/../lib/PropertyBrowser_vc10.lib
}
