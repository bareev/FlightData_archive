#include "editwindow.h"

EditWindow::EditWindow():
    m_edit(noneEdit)
{
}

int EditWindow::newDBWrite(bool newR, QString currentR, QString currentN, QString currentP, QString currLat, QString currLon, QString currDesc)
{
    if (currentR.isEmpty() && !newR)
        return -1;

    if (currentN.isEmpty() && newR)
        return -2;

    float lat, lon;
    if (getEdit() == tsEdit)
    {

        if (currentP.isEmpty() || currLat.isEmpty() || currLon.isEmpty())
            return -3;

        bool ok = false;
        lat = currLat.toFloat(&ok);
        if (!ok)
            return -4;

        lon = currLon.toFloat(&ok);
        if (!ok)
            return -4;
    }

    QVariantMap _map;
    _map.clear();

    _map["newWrite"] = newR;
    _map["who"] = (int)(getEdit());
    _map["description"] = currDesc;

    if (newR)
        _map["name"] = currentN;
    else
        _map["name"] = currentR;

    if (getEdit() == tsEdit)
    {
        _map["place"] = currentP;
        _map["latitude"] = lat;
        _map["longitude"] = lon;
    }

    emit newRec(_map);

    return SUCCESS;
}

