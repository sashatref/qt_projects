#include "extendedtableviewplugin.h"
#include "extendedtableview.h"

ExtendedTableViewPlugin::ExtendedTableViewPlugin(QObject *parent) : QObject(parent)
{
    initialized = false;
}

void ExtendedTableViewPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (initialized)
        return;

    initialized = true;
}

bool ExtendedTableViewPlugin::isInitialized() const
{
    return initialized;
}

QWidget *ExtendedTableViewPlugin::createWidget(QWidget *parent)
{
    return new ExtendedtableView(parent);
}

QString ExtendedTableViewPlugin::name() const
{
    return "ExtendedtableView";
}

QString ExtendedTableViewPlugin::group() const
{
    return "Custom widgets";
}

QIcon ExtendedTableViewPlugin::icon() const
{
    return QIcon();
}

QString ExtendedTableViewPlugin::toolTip() const
{
    return "";
}

QString ExtendedTableViewPlugin::whatsThis() const
{
    return "";
}

bool ExtendedTableViewPlugin::isContainer() const
{
    return false;
}

QString ExtendedTableViewPlugin::domXml() const
{
    return "<ui language=\"c++\">\n"
           " <widget class=\"ExtendedtableView\" name=\"extendedTableView\">\n"
           "  <property name=\"geometry\">\n"
           "   <rect>\n"
           "    <x>0</x>\n"
           "    <y>0</y>\n"
           "    <width>300</width>\n"
           "    <height>200</height>\n"
           "   </rect>\n"
           "  </property>\n"
           " </widget>\n"
           "</ui>\n";
}

QString ExtendedTableViewPlugin::includeFile() const
{
    return "ExtendedTableView/extendedtableview.h";
}
