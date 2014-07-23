#ifndef GSTOREELEMENTTABLEMODEL_H
#define GSTOREELEMENTTABLEMODEL_H

#include <QAbstractTableModel>
#include "gstoretabletype.h"
#include "gcfgstoresetting.h"
class GStoreElementTableModel :  public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit GStoreElementTableModel(QObject *parent = 0, int element = 1);

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

    int element(){ return m_element; }

    void initFromSetting();


signals:
    void sig_channelChanged(int row,int column);
    void sig_quickSet(bool);
private:

    int m_element;
    GStoreTableType m_table[ROW_COUNT][COLUMN_COUNT];
    void init_data();

    void selectAllItems(bool f);
};

#endif // GSTOREELEMENTTABLEMODEL_H
