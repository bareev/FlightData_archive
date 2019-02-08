#ifndef MESSAGE_H
#define MESSAGE_H

#include <QMessageBox>
#include <structs.h>

class Message : public QObject
{
    Q_OBJECT
public:
    Message();
    void ShowMessageBox(int code, msgType type);

private:
    QMessageBox msg;
    QStringList errorsString;
    closeEnable msg_cl;
signals:
    void closeOrEnable(closeEnable);

};

#endif // MESSAGE_H
