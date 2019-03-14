#ifndef ADDWINDOW_H
#define ADDWINDOW_H

#include <QtQuick/QQuickView>
#include <QObject>
#include <descriptionfiles.h>
#include <structs.h>

namespace Ui {
class AddWindow;
}

class AddWindow : public QQuickView
{
    Q_OBJECT

public:
    AddWindow();
    ~AddWindow();
    AddWindow(QString _absDir);
    int init();
    int init(QString _absDir);
    void setAbsDir(QString _absDir){absDir = _absDir; return;}
    Q_INVOKABLE void closeSets();
    Q_INVOKABLE void showDescription(int idx, QStringList s);

    descriptionFiles w_dsc_input;
    descriptionFiles w_dsc_output;

    formType getftype(){return f_type;}
    void setftype(formType ft){f_type = ft; emit paramTextChanged((int)ft); return;}

private:
    QString absDir;
    formType f_type;


signals:
    void onClose();
    void paramTextChanged(int ft);

};

#endif // ADDWINDOW_H
