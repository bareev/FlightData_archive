#ifndef ADDWINDOW_H
#define ADDWINDOW_H

#include <QtQuick/QQuickView>
#include <QObject>

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

private:
    QString absDir;


signals:
    void onClose();

};

#endif // ADDWINDOW_H
