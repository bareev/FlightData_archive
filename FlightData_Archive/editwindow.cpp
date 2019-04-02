#include "editwindow.h"

EditWindow::EditWindow():
    m_edit(noneEdit)
{
    for (int i = 0; i < 4; i++)
        comboboxes.append(QStringList(""));
}

void EditWindow::text()
{
    WhoEdit p = getEdit();
    if (p != noneEdit)
        emit sigNewRecs(getCB(p), (int)p);
    if (p == tsEdit)
        emit sigNewRecs(getCB(placeEdit), ADDITIONAL_COMBO_BOX);
    return;
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

//в combo-box'ы
void EditWindow::newRecs(QStringList s, int t, int w)
{
    WhoEdit type = WhoEdit(t);
    if (type != noneEdit && w == SETTINGS_WINDOW)
        setCB(type, s);

    return;
}

void EditWindow::loadNewCB(QString txt)
{
    if (!txt.isEmpty() && getEdit() == tsEdit)
        emit updateFromMain(txt, SETTINGS_WINDOW);
    return;
}

