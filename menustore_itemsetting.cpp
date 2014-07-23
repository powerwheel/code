#include "menustore_itemsetting.h"
#include <QFrame>
#include <QEvent>
#include <QHBoxLayout>
#include <QKeyEvent>
#include <QDebug>
#include <QCloseEvent>
#include "../mainwindow.h"
#include "../GlobalData/GcfgDataKeyMap.h"
#include <QWheelEvent>
extern MainWindow      *p_GmainWin;

/*
 * 功能：
 * 	  存储项目设置构造函数
 * 参数：
 * 	  1.QWidget *parent: 窗体父对象，默认为0
 * 返回值：
 * 	  无
 */
MenuStore_ItemSetting::MenuStore_ItemSetting(QWidget *parent) :
    QWidget(parent)
{
    initialize();
    setUserDefineStyle();
    setUserDefineContent();
    setWinLayout();
    sigAndSlotConnect();

    p_tableView->select(1,1);
}
/*
 * 功能：
 *      析构函数
 * 参数：
 *      无
 * 返回值：
 * 	  无
 */
MenuStore_ItemSetting::~MenuStore_ItemSetting()
{
    release();
}
void MenuStore_ItemSetting::release()
{
   // delete p_mainFrame;
    delete p_layout;
  //  delete p_mainLayout;
    delete p_tableView;

    for(int i=0; i<6; ++i)
        delete p_storeElementItemModel[i];

    delete p_storeMotorModel;
    delete p_storeUserFuncModel;
    delete p_storeWireModel[0];
    delete p_storeWireModel[1];
    delete p_storeWireModel[2];
}
/*
 * 功能：
 * 	  初始化存储项目设置窗体
 * 参数：
 * 	  无
 * 返回值：
 * 	  无
 */
void MenuStore_ItemSetting::initialize()
{
   // p_mainFrame = new QFrame;
    p_layout = new QHBoxLayout;
   // p_mainLayout = new QHBoxLayout;
    p_tableView = new StoreItemTableView(this);

    for(int i=0; i < 6; i++){
        p_storeElementItemModel[i] = new GStoreElementTableModel(0,i+1);
        p_storeElementItemModel[i]->initFromSetting();
    }

    p_storeMotorModel = new GStoreMotorTableModel;
    p_storeMotorModel->initFromSetting();

    p_storeWireModel[0] = new GStoreWireGroupTableModel(0,1);
    p_storeWireModel[0]->initFromSetting();
    p_storeWireModel[1] = new GStoreWireGroupTableModel(0,2);
    p_storeWireModel[1]->initFromSetting();
    p_storeWireModel[2] = new GStoreWireGroupTableModel(0,3);
    p_storeWireModel[2]->initFromSetting();

    p_storeUserFuncModel = new GStoreUserFunctionTableModel;
    p_storeUserFuncModel->initFromSetting();

    p_tableView->setModel(p_storeElementItemModel[0]);


    p_tableView->installEventFilter(this);
    p_tableView->setObjectName("tableview");

}
/*
 * 功能：
 * 	  设置存储项目窗体内容
 * 参数：
 * 	  无
 * 返回值：
 * 	  无
 */
void MenuStore_ItemSetting::setUserDefineContent()
{

    setAttribute(Qt::WA_TranslucentBackground, true);
    setWindowFlags(Qt::X11BypassWindowManagerHint | Qt::WindowStaysOnTopHint |Qt::FramelessWindowHint | Qt::SubWindow);

}
/*
 * 功能：
 * 	  设置存储项目设置的样式
 * 参数：
 * 	  无
 * 返回值：
 * 	  无
 */
void MenuStore_ItemSetting::setUserDefineStyle()
{
    setStyleSheet("QTableView{\
                    border-width: 1px;\
                    border-color: #808080;\
    border-style: solid;\
    border-radius: 6px;\
    background-color: #394141;\
    color:white;\
    gridline-color:gray;} \
    ");


    p_tableView->setFrameShape(QFrame::NoFrame);  //外观控制
    p_tableView->setFrameShadow(QFrame::Plain);
    p_tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);//关闭鼠标交互
    p_tableView->setSelectionMode(QAbstractItemView::NoSelection);    //不能选择
    p_tableView->setSelectionBehavior(QAbstractItemView::SelectItems);
    p_tableView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//关闭滚动
    p_tableView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    p_tableView->horizontalHeader()->setVisible(false);
    p_tableView->verticalHeader()->setVisible(false);
    p_tableView->horizontalHeader()->setSectionsClickable(false);//关闭点击表头选择
    p_tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//设置表格自动伸缩
    p_tableView->verticalHeader()->setSectionsClickable(false);
    p_tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    p_tableView->setShowGrid(false);

     resize(840,560);
}
/*
 * 功能：
 * 	  设置存储项目设置窗体的Layout
 * 参数：
 * 	  无
 * 返回值：
 * 	  无
 */
void MenuStore_ItemSetting::setWinLayout()
{
    setLayout(p_layout);

    p_layout->addWidget(p_tableView);



    setAttribute(Qt::WA_TranslucentBackground, true);
    setWindowFlags(Qt::X11BypassWindowManagerHint | Qt::WindowStaysOnTopHint |Qt::FramelessWindowHint | Qt::SubWindow);
}
/*
 * 功能：
 * 	  内部的信号槽连接
 * 参数：
 * 	  无
 * 返回值：
 * 	  无
 */
void MenuStore_ItemSetting::sigAndSlotConnect()
{
    for(int i=0; i < 6; i++){
        connect(p_storeElementItemModel[i],SIGNAL(sig_channelChanged(int,int)),this,SLOT(slot_channelChanged(int,int)));
        connect(p_storeElementItemModel[i],SIGNAL(sig_quickSet(bool)),this,SLOT(slot_quickSet(bool)));
    }
    connect(p_storeMotorModel,SIGNAL(sig_channelChanged(int,int)),this,SLOT(slot_channelChanged(int,int)));
    connect(p_storeWireModel[0],SIGNAL(sig_channelChanged(int,int)),this,SLOT(slot_channelChanged(int,int)));
    connect(p_storeWireModel[1],SIGNAL(sig_channelChanged(int,int)),this,SLOT(slot_channelChanged(int,int)));
    connect(p_storeWireModel[2],SIGNAL(sig_channelChanged(int,int)),this,SLOT(slot_channelChanged(int,int)));
    connect(p_storeUserFuncModel,SIGNAL(sig_channelChanged(int,int)),this,SLOT(slot_channelChanged(int,int)));

    connect(p_storeMotorModel,SIGNAL(sig_quickSet(bool)),this,SLOT(slot_quickSet(bool)));
    connect(p_storeWireModel[0],SIGNAL(sig_quickSet(bool)),this,SLOT(slot_quickSet(bool)));
    connect(p_storeWireModel[1],SIGNAL(sig_quickSet(bool)),this,SLOT(slot_quickSet(bool)));
    connect(p_storeWireModel[2],SIGNAL(sig_quickSet(bool)),this,SLOT(slot_quickSet(bool)));
    connect(p_storeUserFuncModel,SIGNAL(sig_quickSet(bool)),this,SLOT(slot_quickSet(bool)));
}

void MenuStore_ItemSetting::showEvent(QShowEvent *)
{
    p_tableView->setFocus();
}
bool MenuStore_ItemSetting::eventFilter(QObject *o, QEvent *event)
{



    if (event->type() == QEvent::KeyPress)
    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);

        //面板事件
        if (keyEvent->modifiers() == PANEL_MODIFIER)
        {
            switch (keyEvent->key())
            {
            case PANEL_UP:
                p_tableView->selectUp();
                return true;
            case PANEL_DOWN:
                p_tableView->selectDown();
                return true;
            case PANEL_LEFT:
                p_tableView->selectLeft();
                return true;
            case PANEL_RIGHT:
                p_tableView->selectRight();
                return true;
            case PANEL_ENTER:
                return false;
            default:
                QApplication::sendEvent(p_GmainWin, event);
                return true;
            }
        }
        return true;       //屏蔽掉其他的按键按下消息
    }

    //按键释放事件
    if (event->type() == QEvent::KeyRelease)
    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);

        //button : ESC from Panel or Keyboard
        if (keyEvent->key() == PANEL_ESC )
        {
//            emit sigClosed();
            this->close();
            return true;
        }
        if(keyEvent->key() == PANEL_ENTER){
            return false;
        }

        //面板事件
        if (keyEvent->modifiers() == PANEL_MODIFIER)
        {
            switch (keyEvent->key())
            {
            default:
                QApplication::sendEvent(p_GmainWin, event);
                return true;
            }
        }
        return true;       //屏蔽掉其他的按键释放消息
    }

    //鼠标滚轮事件
    if (event->type() == QEvent::Wheel)
    {
        QWheelEvent *wheelEvent = static_cast<QWheelEvent*>(event);


        //面板导航编码盘事件
        if (wheelEvent->modifiers() == PANEL_MODIFIER)
        {
            if(wheelEvent->angleDelta().y() > 0){
                p_tableView->selectLeft();
            }else{
                p_tableView->selectRight();
            }

            return true;
        }

        //面板电压、电流量程设置编码盘事件
        if (wheelEvent->modifiers() == PANEL_VOLTRANGE_MODIFIER ||\
            wheelEvent->modifiers() == PANEL_CURRANGE_MODIRFIER)
        {
            QApplication::sendEvent(p_GmainWin, event);
            return true;
        }
    }

    //其它事件
    return QWidget::eventFilter(o,event);
}
/*
 * 功能：
 * 	  内部槽：用于更换显示的数据模型
 * 参数：
 * 	  无
 * 返回值：
 * 	  无
 */
void MenuStore_ItemSetting::slot_channelChanged(int row,int column)
{
    if(row == 1){
        p_tableView->setModel(p_storeElementItemModel[column-1]);
    }else if(column == 1){
        p_tableView->setModel(p_storeMotorModel);
    }else if(column == 2){
        p_tableView->setModel(p_storeWireModel[0]);
    }else if(column == 3){
        p_tableView->setModel(p_storeWireModel[1]);
    }else if(column == 4){
        p_tableView->setModel(p_storeWireModel[2]);
    }else{
        p_tableView->setModel(p_storeUserFuncModel);
    }
    p_tableView->update();
    p_tableView->select(row,column);
    //p_tableView->setFocus();
}
/*
 * 功能：
 * 	  内部槽：当进行快速设置的时候，会对内部的数据模型进行重置，
 *      重置完成后会丢失当前选择用的焦点，此时在界面中对其进行重新选择
 * 参数：
 * 	  bool f: true ALL ON, FALSE: ALL OFF
 * 返回值：
 * 	  无
 */
void MenuStore_ItemSetting::slot_quickSet(bool f)
{
    if(f){
        p_tableView->select(0,1);
    }else{
        p_tableView->select(0,2);
    }
}

void MenuStore_ItemSetting::closeEvent(QCloseEvent *e)
{
    emit sigClose();
    QWidget::closeEvent(e);
}
