#include "descriptionfiles.h"

#include "structs.h"
#include <QtQml/QQmlContext>

descriptionFiles::descriptionFiles()
{
    absDir.clear();
}

descriptionFiles::descriptionFiles(QString _absDir)
{
    setAbsDir(_absDir);
}

descriptionFiles::~descriptionFiles()
{
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

void descriptionFiles::showResize(QStringList s)
{
    emit addNewRow(s);
    show();
}

