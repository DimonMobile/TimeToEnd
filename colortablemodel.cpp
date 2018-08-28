#include "colortablemodel.h"

ColorTableModel::ColorTableModel(QObject *parent) : QAbstractTableModel(parent)
{

}

int ColorTableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return 5;
}

int ColorTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return 5;
}

QVariant ColorTableModel::data(const QModelIndex &index, int role) const
{
    Q_UNUSED(index)
    Q_UNUSED(role)
    return "kek";
}
