#ifndef ADDWINDOW_H
#define ADDWINDOW_H

#include <QtQuick/QQuickView>
#include <QObject>
#include <descriptionfiles.h>

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

private:
    QString absDir;
    descriptionFiles w_dsc_input;
    descriptionFiles w_dsc_output;


signals:
    void onClose();

};

#endif // ADDWINDOW_H
