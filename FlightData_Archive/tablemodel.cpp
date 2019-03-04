#include "tablemodel.h"

tableModel::tableModel()
{
}

// Метод для получения имен ролей через хешированную таблицу.
QHash<int, QByteArray> tableModel::roleNames() const {
    /* То есть сохраняем в хеш-таблицу названия ролей
     * по их номеру
     * */
    QHash<int, QByteArray> roles;
    roles[DateTimeRole] = "date";
    roles[PlaceRole] = "placeStr";
    roles[TypeRole] = "type";
    roles[MessageRole] = "description";

    return roles;
}


// Метод для получения данных из модели
QVariant tableModel::data(const QModelIndex & index, int role) const {

    // Определяем номер колонки, адрес так сказать, по номеру роли
    int columnId = role - Qt::UserRole - 1;
    // Создаём индекс с помощью новоиспечённого ID колонки
    QModelIndex modelIndex = this->index(index.row(), columnId);

    /* И с помощью уже метода data() базового класса
     * вытаскиваем данные для таблицы из модели
     * */
    return QSqlQueryModel::data(modelIndex, Qt::DisplayRole);
}
