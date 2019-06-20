#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSettings>
//#include <message.h>
#include <QVariant>
#include <structs.h>

class Settings// : public Message
{
public:
    Settings();
    ~Settings();
    int initSets();
    void setFileName(QString _fn){fileNameSetts = _fn; return;}
    QString getFileName(){return fileNameSetts;}
    GenSet getValue(){return generalSet;}
    void setValue(GenSet _s){generalSet = _s; return;}
    void writeAll();
    QString cyrilToLatin(QString symbol);
    
private:
    QString cyrilic(QChar symbol);
    QString fileNameSetts;
    QSettings* fileSets;
    GenSet generalSet;
    QVariant readingParam(QString param, QVariant defaultVal, int numberError);

};

#endif // SETTINGS_H
