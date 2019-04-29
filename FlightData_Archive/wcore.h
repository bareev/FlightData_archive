#ifndef WCORE_H
#define WCORE_H

#include <QtQuick/QQuickView>
#include <QObject>
#include <structs.h>


class Wcore : public QQuickView
{
    Q_OBJECT

public:
    Wcore();
    ~Wcore();
    Wcore(QString _absDir);
    int init(QString qmlname, QString context);
    int init(QString _absDir, QString qmlname, QString context);
    void setAbsDir(QString _absDir){absDir = _absDir; return;}
    Q_INVOKABLE void closeSets();
    void showE();

private:
    QString absDir;

signals:
    void onClose();
    void winEnabled(bool e);
};

#endif // WCORE_H
