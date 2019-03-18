#include "addwindow.h"
#include "structs.h"
#include <QtQml/QQmlContext>

AddWindow::AddWindow()
{
    absDir.clear();
    f_type = noneRecord;
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
    (idx == INPUT_FILES?w_dsc_input.showResize(list, getftype()):w_dsc_output.showResize(list, getftype()));
}

int AddWindow::waitForWritetoDB(QString dt, QString tp, QString pl, QString ts, QString inf, QString ouf, QString mes)
{

    if (dt.isEmpty() || tp.isEmpty() || pl.isEmpty() || (inf.isEmpty() && ouf.isEmpty()))
    {
        //showMessage(); //не хватает нужного количества информации
        return -1;
    }

    QVariantMap _map;
    _map["date"] = dt;
    _map["type"] = tp;
    _map["place"] = pl;
    _map["ts"] = ts;
    _map["message"] = mes;

    emit writeNewDB(_map);
    return SUCCESS;
}
