#ifndef MENUSTORE_SELECTITEM_H
#define MENUSTORE_SELECTITEM_H

#include <QWidget>
#include "../Common/storeitemtableview.h"
#include "../GlobalData/gstoreelementtablemodel.h"
#include "../GlobalData/gstoremotortablemodel.h"
#include "../GlobalData/gstorewiregrouptablemodel.h"
#include "../GlobalData/gstoreuserfunctiontablemodel.h"
class QFrame;
class QHBoxLayout;
class MenuStore_ItemSetting : public QWidget
{
    Q_OBJECT
public:
    MenuStore_ItemSetting(QWidget *parent = 0);
    ~MenuStore_ItemSetting();
private:
    void initialize();
    void release();
    void setUserDefineStyle();
    void setUserDefineContent();
    void setWinLayout();
    void sigAndSlotConnect();

signals:
    void sigClose();
private slots:
    void slot_channelChanged(int row,int column);
    void slot_quickSet(bool);
protected:
    void showEvent(QShowEvent *);
    bool eventFilter(QObject *, QEvent *);
    void closeEvent(QCloseEvent *);
private:
  //  QFrame *p_mainFrame;
    QHBoxLayout *p_layout;
   // QHBoxLayout *p_mainLayout;

    StoreItemTableView *p_tableView;
    GStoreElementTableModel *p_storeElementItemModel[6];
    GStoreMotorTableModel *p_storeMotorModel;
    GStoreWireGroupTableModel *p_storeWireModel[3];
    GStoreUserFunctionTableModel *p_storeUserFuncModel;



};

#endif // MENUSTORE_SELECTITEM_H
