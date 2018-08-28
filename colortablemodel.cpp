#include "colortablemodel.h"

#include <QColor>

ColorTableModel::ColorTableModel(QObject *parent) : QAbstractTableModel(parent)
{

}

int ColorTableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return 100;
}

int ColorTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return 2;
}

QVariant ColorTableModel::data(const QModelIndex &index, int role) const
{
    Q_UNUSED(index)
    Q_UNUSED(role)

    switch(role)
    {
    case Qt::DisplayRole:
        if (index.column() == 0)
            return false;
        else
            return QColor::fromRgb(0, 0, 0);
    case Qt::EditRole:
        return data(index, Qt::DisplayRole);
    case Qt::BackgroundColorRole:
        if (index.column() == 1)
            return QColor(data(index, Qt::DisplayRole).toString());
        else
            return QVariant();
    case Qt::TextColorRole:
    {
        if (index.column() == 1)
        {
            QColor src = data(index, Qt::BackgroundColorRole).value<QColor>();
            return QColor::fromRgb(255 - src.red(), 255 - src.green(), 255 - src.blue());
        }
        else
        {
            return QVariant();
        }
    }
    }

    return QVariant();
}


QVariant ColorTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal)
        {
                if (section == 0)
                return "Auto";
            else
                return "Color";
        }
        else
            return QString::number(section);
    }
    else
        return QVariant();
}


Qt::ItemFlags ColorTableModel::flags(const QModelIndex &index) const
{
    Q_UNUSED(index);
    return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
}
