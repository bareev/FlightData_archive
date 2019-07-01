#include "addwindow.h"
#include "structs.h"
#include <QtQml/QQmlContext>

AddWindow::AddWindow()
{
    f_type = noneRecord;
    id_table = -1;
}

void AddWindow::showDescription(int idx, QStringList list)
{
    if (getftype() == newRecord)
        (idx == INPUT_FILES?w_dsc_input.showResize(list, getftype()):w_dsc_output.showResize(list, getftype()));
    else if (getftype() == updateRecord)
    {
        (idx == INPUT_FILES?w_dsc_input.showResize(list, getftype()):w_dsc_output.showResize(list, getftype()));
        ///list = ???; /// доделать!!!
    }
    emit winEnabled(false);
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

    emit writeNewDB(_map, (int)f_type);
    return SUCCESS;
}

void AddWindow::fillData(QVariantMap res)
{
    if (res.isEmpty())
        return;

    QStringList keys = res.keys();
    updateInfo who = noneUpdate;
    for (int i = 0; i < keys.length(); i++)
    {
        QString text = res.value(keys.at(i)).toString();
        QString odd("");
        QString even("");

        if (!keys.at(i).compare("date", Qt::CaseInsensitive))
            who = dateUpdate;
        else if (!keys.at(i).compare("placeStr", Qt::CaseInsensitive))
            who = placeUpdate;
        else if (!keys.at(i).compare("type", Qt::CaseInsensitive))
            who = typeUpdate;
        else if (!keys.at(i).compare("description", Qt::CaseInsensitive))
            who = descriptionUpdate;
        else if (!keys.at(i).compare("ifiles", Qt::CaseInsensitive))
        {
            who = inputUpdate;
            oddevenString(text.split(";"), &odd, &even);
            text = odd;
        }
        else if (!keys.at(i).compare("ofiles", Qt::CaseInsensitive))
        {
            who = outputUpdate;
            oddevenString(text.split(";"), &odd, &even);
            text = odd;
        }
        else if (!keys.at(i).compare("coord", Qt::CaseInsensitive))
            who = coordUpdate;

        emit updateInfoSignal(int(who), tr(text.toUtf8()));
    }

}

void AddWindow::loadNewCB(QString txt)
{
    if (!txt.isEmpty())
        emit updateFromMain(txt, ADD_WINDOW);
    return;
}

void AddWindow::newRecs(QStringList s, int t, int w)
{
    if ((t > 0) && (t < 4) && w == ADD_WINDOW)
        emit sigNewRecs(s, t);
    return;
}
