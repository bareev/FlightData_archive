#ifndef INITIALDIALOG_H
#define INITIALDIALOG_H

#include <wcore.h>

namespace Ui {
class InitialDialog;
}

class InitialDialog : public Wcore
{
    Q_OBJECT

public:
    InitialDialog();
    void setCopy(QString infile, QString outDir);
    void setInFile(QString i){infile = i; return;}
    void setOutDir(QString o){outDir = o; return;}
    QString getDir(){return outDir;}
    QString getFile(){return infile;}
    int getBytesCopy();
    int getBytesCopy(QString infile, QString outDir);
    QString getNewFileName(){return newFileName;}
private:
    QString infile;
    QString outDir;
    QString newFileName;
    quint64 fsize;
public slots:
    void emitbytes(quint64 b);
    void chText(bool);
signals:
    void getbytes(float b);
    void saveCopyText(bool e);

};

#endif // INITIALDIALOG_H
