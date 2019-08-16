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
    bool event(QEvent *event);
    void oddevenString(QStringList input, QString *odd, QString *even, int mod = -1, const char* symbol = ";");
    bool stringListCompare(QStringList input, QStringList output, Qt::CaseSensitivity par = Qt::CaseInsensitive);

private:
    QString absDir;

signals:
    void onClose();
    void winEnabled(bool e);
};

#endif // WCORE_H
