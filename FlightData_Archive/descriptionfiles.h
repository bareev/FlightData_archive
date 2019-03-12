#ifndef DESCRIPTIONFILES_H
#define DESCRIPTIONFILES_H

#include <QtQuick/QQuickView>
#include <QObject>

namespace Ui {
class descriptionFiles;
}

class descriptionFiles : public QQuickView
{
    Q_OBJECT

public:
    descriptionFiles();
    ~descriptionFiles();
    descriptionFiles(QString _absDir);
    int init();
    int init(QString _absDir);
    void setAbsDir(QString _absDir){absDir = _absDir; return;}
    Q_INVOKABLE void closeSets();
    void showResize(QStringList s);

private:
    QString absDir;


signals:
    void onClose();
    void addNewRow(QStringList s);

};

#endif // DESCRIPTIONFILES_H
