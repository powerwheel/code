#ifndef GSTOREUSERFUNCTIONTABLEMODEL_H
#define GSTOREUSERFUNCTIONTABLEMODEL_H

#include <QAbstractTableModel>
#include "gstoretabletype.h"
class GStoreUserFunctionTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit GStoreUserFunctionTableModel(QObject *parent = 0 );

    enum{
        ROW_COUNT = 17,
        COLUMN_COUNT = 7
    };
public:
    int rowCount(const QModelIndex &parent = QModelIndex()) const ;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    Qt::ItemFlags flags(const QModelIndex & index) const;

    void initFromSetting();

signals:
    void sig_channelChanged(int row,int column);
    void sig_quickSet(bool);
private:

    GStoreTableType m_table[ROW_COUNT][COLUMN_COUNT];
    void init_data();

    void selectAllItems(bool f);

};

#endif // GSTOREUSERFUNCTIONTABLEMODEL_H
