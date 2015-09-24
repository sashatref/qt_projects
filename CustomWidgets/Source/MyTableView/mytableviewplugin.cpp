#include "mytableviewplugin.h"
#include "mytableview.h"

MyTableViewPlugin::MyTableViewPlugin(QObject *parent) : QObject(parent)
{
    initialized = false;
}

void MyTableViewPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (initialized)
        return;

    initialized = true;
}

bool MyTableViewPlugin::isInitialized() const
{
    return initialized;
}

QWidget *MyTableViewPlugin::createWidget(QWidget *parent)
{
    return new MyTableView(parent);
}

QString MyTableViewPlugin::name() const
{
    return "MyTableView";
}

QString MyTableViewPlugin::group() const
{
    return "Custom widgets";
}

QIcon MyTableViewPlugin::icon() const
{
    return QIcon();
}

QString MyTableViewPlugin::toolTip() const
{
    return "";
}

QString MyTableViewPlugin::whatsThis() const
{
    return "";
}

bool MyTableViewPlugin::isContainer() const
{
    return false;
}

QString MyTableViewPlugin::domXml() const
{
    return "<ui language=\"c++\">\n"
           " <widget class=\"MyTableView\" name=\"myTableView\">\n"
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

QString MyTableViewPlugin::includeFile() const
{
    return "MyTableView/mytableview.h";
}
