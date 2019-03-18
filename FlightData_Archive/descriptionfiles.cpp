#include "descriptionfiles.h"

#include "structs.h"
#include <QtQml/QQmlContext>

descriptionFiles::descriptionFiles()
{
    absDir.clear();
    f_type = noneRecord;
    input_output = -1;
    readyWrite = false;
}

descriptionFiles::descriptionFiles(QString _absDir)
{
    setAbsDir(_absDir);
}

descriptionFiles::~descriptionFiles()
{
}


void descriptionFiles::onNewDBName(QString name)
{
    readyWrite = true;
    basename = name;
}

int descriptionFiles::init()
{
    if (!absDir.isEmpty())
    {
        setResizeMode(QQuickView::SizeRootObjectToView);
        setSource(QUrl::fromLocalFile(absDir + "/tableModelDescription.qml"));
        rootContext()->setContextProperty("tableModelDesc", this);

        return SUCCESS;
    }
    else
    {
        //ShowMessageBox(3, error);
        return -1;
    }

}

int descriptionFiles::init(QString _absDir)
{
    setAbsDir(_absDir);
    return init();
}

void descriptionFiles::closeSets()
{
    emit onClose();
    return;
}

void descriptionFiles::showResize(QStringList s, formType ft)
{
    emit addNewRow(s);
    setftype(ft);
    emit paramTextChanged((int)ft);
    readyWrite = false;
    show();
}

