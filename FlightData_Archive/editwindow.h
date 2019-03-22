#ifndef EDITWINDOW_H
#define EDITWINDOW_H
#include <wcore.h>

namespace Ui {
class EditWindow;
}

class EditWindow : public Wcore
{
    Q_OBJECT

public:
    EditWindow();
    void setEdit(WhoEdit e){m_edit = e; emit newState((int) e); return;}
    WhoEdit getEdit(){return m_edit;}
    Q_INVOKABLE int newDBWrite(bool newR, QString currentR, QString currentN, QString currentP, QString currLat, QString currLon, QString currDesc);

public slots:

private:
    WhoEdit m_edit;

signals:
    void newState(int e);
    void newRec(QVariantMap _map);
};

#endif // EDITWINDOW_H
