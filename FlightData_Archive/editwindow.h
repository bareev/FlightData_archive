#ifndef EDITWINDOW_H
#define EDITWINDOW_H
#include <wcore.h>

#define ADDITIONAL_COMBO_BOX 4

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
    Q_INVOKABLE void loadFromDB(bool newR, QString name);
    void setCB(WhoEdit e, QStringList i){if (e != noneEdit) {comboboxes.replace(int(e), i);} return;}
    QStringList getCB(WhoEdit e){if (e != noneEdit) {return comboboxes.at(int(e));} else {return (QStringList(""));}}
    void text();
    Q_INVOKABLE void loadNewCB(QString txt);    
    void fillInfo(QString desr, QString parentPl, float lat, float lon);
public slots:
    void newRecs(QStringList s, int t, int w);

private:
    WhoEdit m_edit;
    QList<QStringList> comboboxes;

signals:
    void newState(int e);
    void newRec(QVariantMap _map);
    void sigNewRecs(QStringList s, int t);
    void updateFromMain(QString txt, int w);
    void loadCurrentInfoFromDB(int t, QString name);
    void fillCurrentInfo(int, QString, QString, double, double);
};

#endif // EDITWINDOW_H
