#include "colortablemodel.h"

#include <QDebug>

ColorTableModel::ColorTableModel(QObject *parent) : QAbstractTableModel(parent)
{
    m_values.resize(101);
}

QColor &ColorTableModel::colorAt(int index)
{
    return m_values[index].second;
}

bool &ColorTableModel::autoAt(int index)
{
    return m_values[index].first;
}

int ColorTableModel::colorSize()
{
    return m_values.size();
}

void ColorTableModel::resetData()
{
    for(int i = 0 ; i < colorSize(); ++i)
    {
        colorAt(i) = Qt::white;
        autoAt(i) = true;
    }
    emit dataChanged(createIndex(0,0), createIndex(m_values.size(), 1));
}

void ColorTableModel::processData()
{
    QVector<QPair<int, int>> intervals;
    for(int i = 0 ; i < colorSize(); ++i)
    {
        if (autoAt(i) == false)
        {
            if (intervals.size() == 0)
            {
                intervals.push_back(QPair<int, int>(i, -1));
            }
            else
            {
                intervals[intervals.size()-1].second = i;
                intervals.push_back(QPair<int, int>(i, -1));
            }
        }
    }
    intervals[intervals.size()-1].second = intervals.size()-1;
    for(int i = 0 ; i < intervals.size(); ++i)
    {
        int distance = intervals[i].second - intervals[i].first;
        if (distance < 0) continue;
        float redOffset = (colorAt(intervals[i].second).red() - colorAt(intervals[i].first).red()) / static_cast<float>(distance);
        float greenOffset = (colorAt(intervals[i].second).green() - colorAt(intervals[i].first).green()) / static_cast<float>(distance);
        float blueOffset = (colorAt(intervals[i].second).blue() - colorAt(intervals[i].first).blue()) / static_cast<float>(distance);
        float redResult = colorAt(intervals[i].first).red();
        float greenResult = colorAt(intervals[i].first).green();
        float blueResult = colorAt(intervals[i].first).blue();
        qDebug() << distance << redOffset << greenOffset << blueOffset;
        for(int j = intervals[i].first + 1; j < intervals[i].second; ++j)
        {
            redResult += redOffset;
            greenResult += greenOffset;
            blueResult += blueOffset;
            colorAt(j) = QColor::fromRgb(qRound(redResult), qRound(greenResult), qRound(blueResult));
            emit dataChanged(createIndex(1, j), createIndex(1, j));
        }
    }
}

int ColorTableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_values.size();
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
            return m_values[index.row()].first;
        else
            return m_values[index.row()].second;
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


bool ColorTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    switch(role)
    {
    case Qt::EditRole:
        if (index.column() == 0)
        {
            if (value.type() == QVariant::Bool)
            {
                m_values[index.row()].first = value.toBool();
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            QColor src = QColor(value.toString());
            QColor before = QColor(data(index, Qt::DisplayRole).value<QColor>());
            if (src == before)
            {
                return false;
            }
            else if (src.isValid())
            {
                m_values[index.row()].second = value.value<QColor>();
                m_values[index.row()].first = false;
                emit dataChanged(createIndex(index.row(), 0), createIndex(index.row(), 0));
                processData();
                return true;
            }
            else
            {
                return false;
            }
        }
    }
    return false;
}
