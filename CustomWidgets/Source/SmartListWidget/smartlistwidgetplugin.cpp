#include "smartlistwidgetplugin.h"
#include "smartlist.h"

SmartListWidgetPlugin::SmartListWidgetPlugin(QObject *parent) : QObject(parent)
{
    initialized = false;
}

void SmartListWidgetPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (initialized)
        return;

    initialized = true;
}

bool SmartListWidgetPlugin::isInitialized() const
{
    return initialized;
}

QWidget *SmartListWidgetPlugin::createWidget(QWidget *parent)
{
    return new SmartList(parent);
}

QString SmartListWidgetPlugin::name() const
{
    return "SmartList";
}

QString SmartListWidgetPlugin::group() const
{
    return "Custom widgets";
}

QIcon SmartListWidgetPlugin::icon() const
{
    return QIcon();
}

QString SmartListWidgetPlugin::toolTip() const
{
    return "";
}

QString SmartListWidgetPlugin::whatsThis() const
{
    return "";
}

bool SmartListWidgetPlugin::isContainer() const
{
    return false;
}

QString SmartListWidgetPlugin::domXml() const
{
    return "<ui language=\"c++\">\n"
           " <widget class=\"SmartList\" name=\"smartList\">\n"
           "  <property name=\"geometry\">\n"
           "   <rect>\n"
           "    <x>0</x>\n"
           "    <y>0</y>\n"
           "    <width>150</width>\n"
           "    <height>200</height>\n"
           "   </rect>\n"
           "  </property>\n"
           " </widget>\n"
           "</ui>\n";
}

QString SmartListWidgetPlugin::includeFile() const
{
    return "SmartListWidget/smartlist.h";
}
