#include "message.h"
#include "QApplication"

Message::Message()
{
    msg.close();
    msg_cl = nonecl;

    //перечисление ошибок
    errorsString.clear();
    errorsString.append("Не удаётся открыть файл основных настроек ./config/config.ini. Возможно он не существует или доступен только для чтения");
}

void Message::ShowMessageBox(int code, msgType type)
{
    if (type == error)
    {
        msg_cl = closeT;
        msg.critical(0, "Error", errorsString.at(code));
    }
    else
    {

    }
    emit closeOrEnable(msg_cl);
}
