#include "initialdialog.h"
#include <QFileInfo>

InitialDialog::InitialDialog()
{
    infile.clear();
    outDir.clear();
    newFileName.clear();
    fsize = 0;
}

void InitialDialog::setCopy(QString _infile, QString _outDir)
{
    infile = _infile;
    outDir = _outDir;
    return;
}

int InitialDialog::getBytesCopy()
{
    if (infile.isEmpty() || outDir.isEmpty())
        return -1;

    QFile fi;
    fi.setFileName(infile);

    if (!fi.open(QIODevice::ReadOnly))
        return -2;
    else
        fi.close();

    fsize = QFileInfo(fi).size();


    newFileName = QString(outDir).append("/").append(QFileInfo(infile).fileName());
    QFile fo;
    fo.setFileName(newFileName);
    fo.remove();
    //connect(&fi, SIGNAL(bytesWritten(qint64)), this, SLOT(emitbytes(qint64)));

    bool res = fi.copy(newFileName);

    if (!res)
        return -3;
    else
        return SUCCESS;
}

int InitialDialog::getBytesCopy(QString infile, QString outDir)
{
    init(infile, outDir);
    return getBytesCopy();
}

void InitialDialog::emitbytes(quint64 bytes)
{
    float b = 0;
    if (fsize > 0)
        b = bytes / fsize;
    emit getbytes(b);
}
