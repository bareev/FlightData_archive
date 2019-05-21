#include "tablemodel.h"
#include <QSqlRecord>
#include <QDateTime>
#include <QSqlField>

tableModel::tableModel()
{
    ac = noneAct;
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

QVariantMap tableModel::getData(int row)
{
    QVariantMap res;
    res.clear();
    for (int col = 0; col < 4; col++)
    {
        QModelIndex currentIndex = QAbstractTableModel::index(row, col);
        QVariant var = data(currentIndex, col + 1 + Qt::UserRole);
        QString field = record(row).fieldName(col);
        res[field] = var;
    }

    return res;
}



