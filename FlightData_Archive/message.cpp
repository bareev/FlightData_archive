#include "message.h"
#include "QApplication"

Message::Message()
{
    msg.close();
    msg_cl = nonecl;

    //перечисление ошибок
    errorsString.clear();
    errorsString.append("Не удаётся открыть файл основных настроек /config/config.ini. Возможно он не существует или доступен только для чтения");
    errorsString.append("Не настроена директория с данными. Используется путь по умолчанию");
    errorsString.append("Не удалось загрузить основную форму. Возможно не найден файл mainWindow.qml");
    errorsString.append("Не удалось загрузить форму настроек. Возможно не найден файл settingsWindow.qml");
    errorsString.append("Не удалось загрузить форму кнопок. Возможно не найден файл WindowButton.qml");
    errorsString.append("Не указан файл базы данных. Вы можете выбрать другой файл в настройках, воссоздать архив в базу или продолжить работу с пустым файлом по умолчанию");
    errorsString.append("Не удалось открыть файл базы данных. Вы можете выбрать другой файл и директорию в настройках, воссоздать архив в базу или продолжить работу с пустым файлом по умолчанию");
}

void Message::ShowMessageBox(int code, msgType type)
{
    if (type == critical)
    {
        msg_cl = closeT;
        msg.critical(0, "Error", errorsString.at(code));
    }
    else if (type == error)
    {
        msg_cl = enableT;
        msg.critical(0, "Error", errorsString.at(code));
    }
    else if (type == warning)
    {
        msg_cl = enableT;
        msg.warning(0, "Warning", errorsString.at(code));
    }
}
