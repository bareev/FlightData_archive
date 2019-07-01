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

bool Wcore::event(QEvent *event)
{
    if (event->type() == QEvent::Close)
    {
        closeSets();
    }
    return QQuickView::event(event);
}

void Wcore::oddevenString(QStringList input, QString *odd, QString *even, int mod, const char *symbol)
{
    odd->clear();
    even->clear();
    if (mod == -1)
        mod = 2; //четные - нечетные

    for (int i = 0; i < input.length(); i++)
    {
        if (i % mod == 0)
            odd->append(input.at(i)).append(symbol);
        else
            even->append(input.at(i)).append(symbol);
    }

    if (odd->length() > 0)
        odd->chop(1);

    if (even->length() > 0)
        even->chop(1);
}

void Wcore::closeSets()
{
    emit onClose();
    return;
}

void Wcore::showE()
{
    emit winEnabled(true);
    show();
}
