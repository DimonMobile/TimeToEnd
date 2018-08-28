#ifndef COLORTABLEMODEL_H
#define COLORTABLEMODEL_H

#include <QAbstractTableModel>

class ColorTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    ColorTableModel(QObject *parent = nullptr);
    ColorTableModel(const ColorTableModel &srcModel);
    ColorTableModel operator = (const ColorTableModel &srcModel);
    virtual int rowCount(const QModelIndex &parent) const override;
    virtual int columnCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;
};

#endif // COLORTABLEMODEL_H
