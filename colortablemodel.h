#ifndef COLORTABLEMODEL_H
#define COLORTABLEMODEL_H

#include <QAbstractTableModel>
#include <QColor>

class ColorTableModel : public QAbstractTableModel
{
    Q_OBJECT
private:
    QVector<QPair<bool, QColor>> m_values;
public:
    ColorTableModel(QObject *parent = nullptr);
    ColorTableModel(const ColorTableModel &srcModel);
    ColorTableModel operator = (const ColorTableModel &srcModel);
    QColor& colorAt(int index);
    bool& autoAt(int index);
    int colorSize();
    void resetData();
    void processData();
    virtual int rowCount(const QModelIndex &parent) const override;
    virtual int columnCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    virtual Qt::ItemFlags flags(const QModelIndex &index) const override;
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role) override;
};

#endif // COLORTABLEMODEL_H
