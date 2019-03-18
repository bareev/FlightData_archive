#ifndef DESCRIPTIONFILES_H
#define DESCRIPTIONFILES_H

#include <QtQuick/QQuickView>
#include <QObject>
#include <structs.h>

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
    void showResize(QStringList s, formType f);

    formType getftype(){return f_type;}
    void setftype(formType ft){f_type = ft; return;}

    void setInputOutput(int p){input_output = p; emit iochange(p); return;}
    int getInputOutput(){return input_output;}

public slots:
    void onNewDBName(QString name);

private:
    QString absDir;
    formType f_type;
    int input_output;
    bool readyWrite;
    QString basename;

signals:
    void onClose();
    void addNewRow(QStringList s);
    void iochange(int p);
    void paramTextChanged(int ft);

};

#endif // DESCRIPTIONFILES_H
