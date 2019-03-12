#include "addwindow.h"
#include "structs.h"
#include <QtQml/QQmlContext>

AddWindow::AddWindow()
{
    absDir.clear();
}

AddWindow::AddWindow(QString _absDir)
{
    setAbsDir(_absDir);
}

AddWindow::~AddWindow()
{
}

int AddWindow::init()
{
    if (!absDir.isEmpty())
    {
        setResizeMode(QQuickView::SizeRootObjectToView);
        setSource(QUrl::fromLocalFile(absDir + "/windowAddNew.qml"));
        rootContext()->setContextProperty("windowAdd", this);

        return SUCCESS;
    }
    else
    {
        //ShowMessageBox(3, error);
        return -1;
    }

    int res = w_dsc_input.init(absDir);
    if (res != SUCCESS)
    {
        //
        return -1;
    }
    w_dsc_input.hide();

    res = w_dsc_output.init(absDir);
    if (res != SUCCESS)
    {
        //
        return -1;
    }
    w_dsc_output.hide();


}

int AddWindow::init(QString _absDir)
{
    setAbsDir(_absDir);
    return init();
}

void AddWindow::closeSets()
{
    emit onClose();
    return;
}

void AddWindow::showDescription(int idx, QStringList list)
{
    (idx == 0?w_dsc_input.showResize(list):w_dsc_output.showResize(list));
}
