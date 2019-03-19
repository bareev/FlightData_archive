#include "wcore.h"
#include <QtQml/QQmlContext>

Wcore::Wcore()
{
    absDir.clear();
}

Wcore::Wcore(QString _absDir)
{
    setAbsDir(_absDir);
}

Wcore::~Wcore()
{
}

int Wcore::init(QString qmlname, QString context)
{
    if (!absDir.isEmpty())
    {
        setResizeMode(QQuickView::SizeRootObjectToView);
        setSource(QUrl::fromLocalFile(absDir + qmlname));
        rootContext()->setContextProperty(context, this);
        return SUCCESS;
    }
    else
    {
        //ShowMessageBox(3, error);
        return -1;
    }

}

int Wcore::init(QString _absDir, QString qmlname, QString context)
{
    setAbsDir(_absDir);
    return init(qmlname, context);
}

void Wcore::closeSets()
{
    emit onClose();
    return;
}
