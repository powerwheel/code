#include "gstorewiregrouptablemodel.h"
#include "../Common/storeitemtableview.h"
#include "gpckdatabasicitem.h"
#include "gcfgstoresetting.h"
/********************************接线组对应的存储项目模型*********************************/
/*
 * 功能：
 * 	  接线组1-3表格视图的数据模型构造函数
 * 参数：
 * 	  1.QObject *parent: 父对象，默认为0
 *	  2.int wireG: 所属通道(1-3)
 * 返回值：
 * 	  无
 */
GStoreWireGroupTableModel::GStoreWireGroupTableModel(QObject *parent ,int wireG) :
    QAbstractTableModel(parent)
{
    m_group = wireG;
    init_data();

}
/*******************************接线组对应的存储项目模型***********************************/
/*
 * 功能：
 * 	  返回显示所用的行数
 * 参数：
 * 	  1.QModelIndex &parent: 根节点index
 * 返回值：
 * 	  int:行数
 */
int GStoreWireGroupTableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return ROW_COUNT;
}
/*******************************接线组对应的存储项目模型***********************************/
/*
 * 功能：
 * 	  返回显示所用的列数
 * 参数：
 * 	  1.QModelIndex &parent: 根节点index
 * 返回值：
 * 	  int:列数
 */
int GStoreWireGroupTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return COLUMN_COUNT;
}
/*******************************接线组对应的存储项目模型***********************************/
/*
 * 功能：
 * 	  返回要显示的数据
 * 参数：
 * 	  1.QModelIndex &index: 请求获取的数据索引
 *	  2.int role：要显示的对象类型
 * 返回值：
 * 	  QVariant:显示的数据
 */
QVariant GStoreWireGroupTableModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    int column = index.column();
    switch(role){
    case Qt::DisplayRole:
        return m_table[row][column].text();
    case Qt::TextAlignmentRole:
        return Qt::AlignCenter;
    case IsRadioRole:
        if(m_table[row][column].type() == GStoreTableType::RadioButton){
            return true;
        }else{
            return false;
        }
    case IsCheckRole:
        if(m_table[row][column].type() == GStoreTableType::Item){
            return true;
        }else{
            return false;
        }
    case IsPushButtonRole:
        if(m_table[row][column].type() == GStoreTableType::PushButton){
            return true;
        }else{
            return false;
        }
    case RadioSelectedRole:
        if(m_table[row][column].type() == GStoreTableType::RadioButton ||
                m_table[row][column].type() == GStoreTableType::Item ||
                m_table[row][column].type() == GStoreTableType::PushButton){
            return m_table[row][column].isChecked();
        }else{
            return QVariant();
        }
    default:
        return QVariant();
    }
}
/*******************************接线组对应的存储项目模型***********************************/
/*
 * 功能：
 * 	  设置表格数据
 * 参数：
 * 	  1.QModelIndex &index: 要设置的数据索引
 *	  2.int role：要显示的对象类型
 * 返回值：
 * 	  bool:是否设置成功
 */
bool GStoreWireGroupTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    int row = index.row();
    int column = index.column();
    if(role == RadioSelectedRole){
        if(row == 1 || row == 2){
            if(column != 0)
                emit sig_channelChanged(row,column);
            return QAbstractTableModel::setData(index,value,role);
        }else if(row == 0){
            if(column == 1){
                m_table[0][1].setChecked(value.toBool());
                if(!value.toBool())
                    selectAllItems(true);

                return true;
            }else if(column == 2){
                m_table[0][2].setChecked(value.toBool());
                if(!value.toBool())
                    selectAllItems(false);
                return true;
            }
        }else{
            m_table[row][column].setChecked(value.toBool());
            GcfgStoreSetting *setting = GcfgStoreSetting::instance();
            GcfgStoreItemSetting::Item_Type type = static_cast<GcfgStoreItemSetting::Item_Type>(m_group + 6);
            if(value.toBool()){
                setting->itemSetting(type)->addItem(m_table[row][column].itemIndex());
            }else{
                setting->itemSetting(type)->removeItem(m_table[row][column].itemIndex());
            }
        }
        return true;
    }else{
        return QAbstractTableModel::setData(index,value,role);
    }

}
/*******************************接线组对应的存储项目模型***********************************/
/*
 * 功能：
 * 	  设置对应数据项的标志位
 * 参数：
 * 	  1.QModelIndex &index: 要设置的数据索引
 * 返回值：
 * 	  Qt::ItemFlags:该数据项对应的标志
 */
Qt::ItemFlags GStoreWireGroupTableModel::flags(const QModelIndex &index) const
{
    int row = index.row();
    int column = index.column();
    Qt::ItemFlags flags = QAbstractTableModel::flags(index);
    if(m_table[row][column].type() == GStoreTableType::InValid){
        flags &= ~Qt::ItemIsSelectable;
        flags &= ~Qt::ItemIsEnabled;
        return flags;
    }else{
        return flags;
    }

}
/*******************************接线组对应的存储项目模型***********************************/
/*
 * 功能：
 * 	  选择/关闭 所有项目
 * 参数：
 * 	  1.bool f: 选择所有项目还是关闭所有项目
 * 返回值：
 * 	  无
 */
void GStoreWireGroupTableModel::selectAllItems(bool f)
{

    beginResetModel();
    for( int i = 0; i <= ROW_COUNT; i++){
        for(int j = 0; j <= COLUMN_COUNT; ++j){
            if(m_table[i][j].type() == GStoreTableType::Item){
                m_table[i][j].setChecked(f);
            }
        }
    }
    endResetModel();


    //Sync to Setting Object
    GcfgStoreSetting *setting = GcfgStoreSetting::instance();
    GcfgStoreItemSetting::Item_Type type = static_cast<GcfgStoreItemSetting::Item_Type>(m_group + 6);
    if(f){
        for( int i = 0; i <= ROW_COUNT; i++){
            for(int j = 0; j <= COLUMN_COUNT; ++j){
                if(m_table[i][j].type() == GStoreTableType::Item){
                    setting->itemSetting(type)->addItem(m_table[i][j].itemIndex());
                }
            }
        }
    }else{
        setting->itemSetting(type)->clearAll();
    }
    emit sig_quickSet(f);
}
/*******************************接线组对应的存储项目模型***********************************/
/*
 * 功能：
 * 	  从存储配置类中读取预先存储的设置
 * 参数：
 * 	  无
 * 返回值：
 * 	  无
 */
void GStoreWireGroupTableModel::initFromSetting()
{
    GcfgStoreSetting *setting = GcfgStoreSetting::instance();

    GcfgStoreItemSetting::Item_Type type;
    if(m_group == 1){
        type = GcfgStoreItemSetting::WireGroup1;
    }else if(m_group ==2){
        type = GcfgStoreItemSetting::WireGroup2;
    }else if(m_group == 3){
        type = GcfgStoreItemSetting::WireGroup3;
    }

    if(setting->itemSetting(type)->isEmpty())
        return;

   // selectAllItems(false);

    beginResetModel();
    for( int i = 0; i <= ROW_COUNT; i++){
        for(int j = 0; j <= COLUMN_COUNT; ++j){
            if(m_table[i][j].type() == GStoreTableType::Item){
                int idx = m_table[i][j].itemIndex();
                if(setting->itemSetting(type)->hasItem(idx)){
                    m_table[i][j].setChecked(true);
                }
            }
        }
    }
    endResetModel();

}
/*******************************接线组对应的存储项目模型***********************************/
/*
 * 功能：
 * 	  初始化显示数据
 * 参数：
 * 	  无
 * 返回值：
 * 	  无
 */
void GStoreWireGroupTableModel::init_data()
{
    for(int i = 0; i < ROW_COUNT; ++i){
        m_table[i][0].setType(GStoreTableType::InValid);
    }

    m_table[0][0].setText("Quick Set");
    m_table[1][0].setText("Channel");
   // m_table[2][0].setText("Basic Item");

    m_table[0][1].setType(GStoreTableType::PushButton);
    m_table[0][1].setText("ALL ON");
    m_table[0][1].setChecked(false);

    m_table[0][2].setType(GStoreTableType::PushButton);
    m_table[0][2].setText("ALL OFF");
    m_table[0][2].setChecked(false);

    m_table[1][1].setType(GStoreTableType::RadioButton);
    m_table[1][1].setText(QString("ELEMENT1"));

    m_table[1][2].setType(GStoreTableType::RadioButton);
    m_table[1][2].setText(QString("ELEMENT2"));

    m_table[1][3].setType(GStoreTableType::RadioButton);
    m_table[1][3].setText(QString("ELEMENT3"));

    m_table[1][4].setType(GStoreTableType::RadioButton);
    m_table[1][4].setText(QString("ELEMENT4"));

    m_table[1][5].setType(GStoreTableType::RadioButton);
    m_table[1][5].setText(QString("ELEMENT5"));

    m_table[1][6].setType(GStoreTableType::RadioButton);
    m_table[1][6].setText(QString("ELEMENT6"));


    m_table[2][1].setType(GStoreTableType::RadioButton);
    m_table[2][1].setText(QString("Motor"));
    m_table[2][1].setChecked(false);

    m_table[2][2].setType(GStoreTableType::RadioButton);
    m_table[2][2].setText(QString("ΣA"));


    m_table[2][3].setType(GStoreTableType::RadioButton);
    m_table[2][3].setText(QString("ΣB"));


    m_table[2][4].setType(GStoreTableType::RadioButton);
    m_table[2][4].setText(QString("ΣC"));

    m_table[2][5].setType(GStoreTableType::RadioButton);
    m_table[2][5].setText(QString("User Func."));



    if(m_group == 1){
        m_table[2][2].setChecked(true);
    }else if(m_group == 2){
        m_table[2][3].setChecked(true);
    }else if(m_group == 3){
        m_table[2][4].setChecked(true);
    }


//    m_table[1][11].setType(GStoreTableType::RadioButton);
//    m_table[1][11].setText(QString("User Func."));
//    m_table[1][11].setChecked(false);




    GpckDataBasicItem basic_item;

    int cur_row = 4;
    m_table[cur_row][0].setText("Item");
    int col = 1;
    for(int i = GpckDataBasicItem::ItemUrms; i <= GpckDataBasicItem::ItemWQ; ++i){
        m_table[cur_row][col].setType(GStoreTableType::Item);
        m_table[cur_row][col].setText(basic_item.getItemName(i));
        m_table[cur_row][col].setItemIndex(i);

        ++col;
        if(col == COLUMN_COUNT){
            cur_row++;
            col = 1;
        }
    }

    for(int i = GpckDataBasicItem::ItemDeltaF1; i <= GpckDataBasicItem::ItemPhiUi_Ik; ++i){
        m_table[cur_row][col].setType(GStoreTableType::Item);
        m_table[cur_row][col].setText(basic_item.getItemName(i));
        m_table[cur_row][col].setItemIndex(i);

        ++col;
        if(col == COLUMN_COUNT){
            cur_row++;
            col = 1;
        }
    }
}
