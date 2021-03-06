#ifndef ADDWINDOW_H
#define ADDWINDOW_H

#include <QtQuick/QQuickView>
#include <descriptionfiles.h>
#include <wcore.h>

namespace Ui {
class AddWindow;
}

class AddWindow : public Wcore
{
    Q_OBJECT

public:
    AddWindow();
    Q_INVOKABLE void showDescription(int idx, QStringList s);
    Q_INVOKABLE int waitForWritetoDB(QString dt, QString tp, QString pl, QString ts, QString inf, QString ouf, QString mes);
    Q_INVOKABLE void loadNewCB(QString txt);

    descriptionFiles w_dsc_input;
    descriptionFiles w_dsc_output;

    formType getftype(){return f_type;}
    void setftype(formType ft){f_type = ft; emit paramTextChanged((int)ft); return;}

public slots:
    void newRecs(QStringList s, int t, int w);

private:
    formType f_type;

signals:
    void paramTextChanged(int ft);
    void writeNewDB(QVariantMap param);
    void sigNewRecs(QStringList s, int t);
    void updateFromMain(QString txt, int w);
};

#endif // ADDWINDOW_H
