#include "plugincollection.h"
#include "ExtendedTableView/extendedtableviewplugin.h"
#include "MyTableView/mytableviewplugin.h"
#include "RichLabel/richlabelplugin.h"
#include "SmartListWidget/smartlistwidgetplugin.h"
#include "ChooseList/chooselistplugin.h"

PluginsCollection::PluginsCollection(QObject*)
{
    widgets.append(new ExtendedTableViewPlugin(this));
    widgets.append(new MyTableViewPlugin(this));
    widgets.append(new RichLabelPlugin(this));
    widgets.append(new ChooseListPlugin(this));
    widgets.append(new SmartListWidgetPlugin(this));
}

QList<QDesignerCustomWidgetInterface *> PluginsCollection::customWidgets() const
{
    return widgets;
}
