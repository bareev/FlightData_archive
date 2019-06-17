#include "descriptionfiles.h"

descriptionFiles::descriptionFiles()
{
    f_type = noneRecord;
    input_output = -1;
    readyWrite = false;
}


void descriptionFiles::onNewDBName(QString name)
{
    readyWrite = true;
    basename = name;
}

void descriptionFiles::showResize(QStringList s, formType ft)
{
    emit addNewRow(s);
    setftype(ft);
    emit paramTextChanged((int)ft);
    readyWrite = false;
    showE();
}

void descriptionFiles::writeNewDB(QString filesAndMessage)
{
    if (f_type != noneRecord && !filesAndMessage.isEmpty())
    {
        QStringList separatString = filesAndMessage.split("%");
        emit recOrUp(int(f_type), basename, separatString);
    }
}

