#ifndef TABLEMODEL_H
#define TABLEMODEL_H
#include <QSqlQueryModel>
#include "structs.h"

class tableModel : public QSqlQueryModel
{
public:
    explicit tableModel();

    // Перечисляем все роли, которые будут использоваться в TableView
    enum Roles {
        DateTimeRole = Qt::UserRole + 1,    // дата и время
        TypeRole,                       // тип станции
        PlaceRole,                     // место полётов
        MessageRole                     // сообщение
    };

    // Переопределяем метод, который будет возвращать данные
    Q_INVOKABLE QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
    QVariantMap getData(int row);

private:
    action ac;

public:
    action getAc(){return ac;}

protected:
    /* хешированная таблица ролей для колонок.
     * Метод используется в дебрях базового класса QAbstractItemModel,
     * от которого наследован класс QSqlQueryModel
     * */
    QHash<int, QByteArray> roleNames() const;
};

#endif // TABLEMODEL_H
