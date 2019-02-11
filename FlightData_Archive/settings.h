#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSettings>
#include <message.h>
#include <QVariant>

class Settings : public Message
{
public:
    Settings();
    int init();

    void setFileName(QString _fn){fileNameSetts = _fn; return;}
    QString getFileName(){return fileNameSetts;}

    GenSet getValue(){return generalSet;}
    void setValue(GenSet _s){generalSet = _s; return;}
    
private:
    QString fileNameSetts;
    QSettings fileSets;
    GenSet generalSet;

};

#endif // SETTINGS_H
