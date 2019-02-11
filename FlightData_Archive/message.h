#ifndef MESSAGE_H
#define MESSAGE_H

#include <QMessageBox>
#include <structs.h>

class Message
{

public:
    Message();
    void ShowMessageBox(int code, msgType type);
    closeEnable getState(){return msg_cl;}
    void setState(closeEnable ce_){msg_cl = ce_; return;}

private:
    QMessageBox msg;
    QStringList errorsString;
    closeEnable msg_cl;
signals:
    void closeOrEnable(closeEnable);

};

#endif // MESSAGE_H
