#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSettings>
#include <message.h>
#include <QVariant>

class Settings : public Message
{
public:
    Settings();
    void init();

    void setFileName(QString _fn){fileNameSetts = _fn; return;}
    QString getFileName(){return fileNameSetts;}

    QVariant getValue(QString param);
    int setValue(QVariant val);
    
private:
    QString fileNameSetts;
    QSettings generalSets;

};

#endif // SETTINGS_H
