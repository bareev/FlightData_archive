#include "addwindow.h"
#include "structs.h"
#include <QtQml/QQmlContext>

AddWindow::AddWindow()
{
    f_type = noneRecord;
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

void AddWindow::newRecs(QStringList s, int t)
{
    emit sigNewRecs(s, t);
    return;
}
