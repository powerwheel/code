#include <QMouseEvent>
#include <QKeyEvent>
#include <QApplication>
#include <QDebug>
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QPalette>
#include <QWheelEvent>
#include <QEvent>
#include "storeitemtableview.h"
#include "../mainwindow.h"
#include "../GlobalData/GcfgDataKeyMap.h"
extern MainWindow      *p_GmainWin;
/*
 * 功能：
 *      tableView中自定义的委托显示控件构造函数
 * 参数：
 *      QObject *p,父对象
 * 返回值：
 * 	  无
 */
SelectButtonItemDelegate::SelectButtonItemDelegate(QObject *p)
        : QStyledItemDelegate(p)
{
    // nothing
    style_btn = new QPushButton;
    style_btn->setVisible(false);
    style_btn->setStyleSheet("QPushButton{background-color: #394141;\
                border-radius:3px; \
                border: 1px solid gray; \
                color:white;\
                }");

    style_checkbox = new QCheckBox;
    style_radiobutton = new QRadioButton;
    style_checkbox->setVisible(false);
    style_radiobutton->setVisible(false);
    style_checkbox->setStyleSheet("QCheckBox{background-color: #394141;color:white;}");
    style_radiobutton->setStyleSheet("QRadioButton{background-color: #394141;color:white;}");


}

SelectButtonItemDelegate::~SelectButtonItemDelegate()
{
    delete style_btn;
    delete style_checkbox;
    delete style_radiobutton;
}

/*
 * 功能：
 *      重载重绘函数
 * 参数：
 *      QPainter *painter:painter const QStyleOptionViewItem &option:绘制选项 const QModelIndex &index：索引
 * 返回值：
 * 	  无
 */
void SelectButtonItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (index.data(IsRadioRole).canConvert<bool>() && index.data(IsRadioRole).value<bool>()) {

        drawRadioButton(painter,option,index);

    }else if(index.data(IsCheckRole).canConvert<bool>() && index.data(IsCheckRole).value<bool>()){
        drawCheckBox(painter,option,index);
    }else if(index.data(IsPushButtonRole).canConvert<bool>() && index.data(IsPushButtonRole).value<bool>()){
        drawPushButton(painter,option,index);
    }
    else
        QStyledItemDelegate::paint(painter, option, index);
}

/*
 * 功能：
 *      在单元格内画一个RadioButton
 * 参数：
 *      QPainter *painter:painter const QStyleOptionViewItem &option:绘制选项 const QModelIndex &index：索引
 * 返回值：
 * 	  无
 */
void SelectButtonItemDelegate::drawRadioButton(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
//    int radioButtonWidth = QApplication::style()->pixelMetric(QStyle::PM_ExclusiveIndicatorWidth, &option);
//    int radioButtonHeight = QApplication::style()->pixelMetric(QStyle::PM_ExclusiveIndicatorHeight, &option);
//    int spacing = QApplication::style()->pixelMetric(QStyle::PM_RadioButtonLabelSpacing, &option);


//    QStyleOptionViewItem myOption = option;
//    int left = myOption.rect.left();
//    myOption.rect.setLeft(left + spacing  + radioButtonWidth);
//    myOption.text = index.data().toString();


//    QApplication::style()->drawControl(QStyle::CE_RadioButtonLabel, &myOption, painter);
//    QApplication::style()->drawItemText(painter,myOption.rect,Qt::AlignCenter,myOption.palette,true,myOption.text);
//    myOption.rect.setLeft(left + spacing );
//    myOption.rect.setWidth(radioButtonWidth);
//    myOption.rect.setHeight(radioButtonHeight);
//    int y = (option.rect.height() - radioButtonHeight) / 2;
//    if(y>0){
//        myOption.rect.adjust(0,y,0,y);
//    }


//    if (index.data(RadioSelectedRole).canConvert<bool>()) {

//        bool radioButtonSelected = index.data(RadioSelectedRole).value<bool>();
//        myOption.state |= radioButtonSelected ? QStyle::State_On : QStyle::State_Off;
//    }

//    if(option.state & QStyle::State_HasFocus){
//         QApplication::style()->drawPrimitive(QStyle::PE_FrameFocusRect, &option, painter);
//    }

//    QApplication::style()->drawPrimitive(QStyle::PE_IndicatorRadioButton, &myOption, painter);

    QStyleOptionButton myOption;
    myOption.initFrom(style_radiobutton);
    myOption.rect = option.rect;
    myOption.rect.adjust(2,2,-2,-2);
    myOption.text = index.data().toString();
    if(option.state & QStyle::State_HasFocus)
        myOption.state |= QStyle::State_HasFocus;
    myOption.state |= QStyle::State_Enabled;
     if (index.data(RadioSelectedRole).canConvert<bool>()) {

         bool pushButtonClicked = index.data(RadioSelectedRole).value<bool>();
         myOption.state |= pushButtonClicked ? QStyle::State_On : QStyle::State_Off;
     }
   myOption.features |= QStyleOptionButton::DefaultButton;

   QApplication::style()->drawControl(QStyle::CE_RadioButton,&myOption,painter,style_radiobutton);

}
/*
 * 功能：
 *      在单元格内画一个CheckBox
 * 参数：
 *      QPainter *painter:painter const QStyleOptionViewItem &option:绘制选项 const QModelIndex &index：索引
 * 返回值：
 * 	  无
 */
void SelectButtonItemDelegate::drawCheckBox(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
//    int checkButtonWidth = QApplication::style()->pixelMetric(QStyle::PM_ExclusiveIndicatorWidth, &option);
//    int checkButtonHeight = QApplication::style()->pixelMetric(QStyle::PM_ExclusiveIndicatorHeight, &option);
//    int spacing = QApplication::style()->pixelMetric(QStyle::PM_CheckBoxLabelSpacing, &option);


//    QStyleOptionViewItem myOption = option;
//    int left = myOption.rect.left();
//    myOption.rect.setLeft(left + spacing  + checkButtonWidth);
//    myOption.text = index.data().toString();


//    QApplication::style()->drawControl(QStyle::CE_CheckBoxLabel, &myOption, painter);
//    QApplication::style()->drawItemText(painter,myOption.rect,Qt::AlignCenter,myOption.palette,true,myOption.text);

//    myOption.rect.setLeft(left + spacing );
//    myOption.rect.setWidth(checkButtonWidth);
//    myOption.rect.setHeight(checkButtonHeight);
//    int y = (option.rect.height() - checkButtonHeight) / 2;
//    if(y>0){
//        myOption.rect.adjust(0,y,0,y);
//    }


//    if (index.data(RadioSelectedRole).canConvert<bool>()) {

//        bool checkButtonSelected = index.data(RadioSelectedRole).value<bool>();
//        myOption.state |= checkButtonSelected ? QStyle::State_On : QStyle::State_Off;
//    }
//    if(option.state & QStyle::State_HasFocus){
//         QApplication::style()->drawPrimitive(QStyle::PE_FrameFocusRect, &option, painter);
//    }
//    QApplication::style()->drawPrimitive(QStyle::PE_IndicatorCheckBox, &myOption, painter);

    QStyleOptionButton myOption;
    myOption.initFrom(style_checkbox);
    myOption.rect = option.rect;
    myOption.rect.adjust(2,2,-2,-2);
    myOption.text = index.data().toString();
    if(option.state & QStyle::State_HasFocus)
        myOption.state |= QStyle::State_HasFocus;
    myOption.state |= QStyle::State_Enabled;
     if (index.data(RadioSelectedRole).canConvert<bool>()) {

         bool pushButtonClicked = index.data(RadioSelectedRole).value<bool>();
         myOption.state |= pushButtonClicked ? QStyle::State_On : QStyle::State_Off;
     }
   myOption.features |= QStyleOptionButton::DefaultButton;

   QApplication::style()->drawControl(QStyle::CE_CheckBox,&myOption,painter,style_checkbox);

}

void SelectButtonItemDelegate::drawPushButton(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
       QStyleOptionButton myOption;
       myOption.initFrom(style_btn);
       myOption.rect = option.rect;
       myOption.rect.adjust(2,2,-2,-2);
       myOption.text = index.data().toString();
       if(option.state & QStyle::State_HasFocus)
           myOption.state |= QStyle::State_HasFocus;
       myOption.state |= QStyle::State_Enabled;
        if (index.data(RadioSelectedRole).canConvert<bool>()) {

            bool pushButtonClicked = index.data(RadioSelectedRole).value<bool>();
            myOption.state |= pushButtonClicked ? QStyle::State_Sunken : QStyle::State_Raised;
        }
      myOption.features |= QStyleOptionButton::DefaultButton;

      QApplication::style()->drawControl(QStyle::CE_PushButton,&myOption,painter,style_btn);


}


QSize SelectButtonItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QSize s = QStyledItemDelegate::sizeHint(option, index);
    if (index.data(IsRadioRole).value<bool>()) {

        int radioButtonHeight = QApplication::style()->pixelMetric(QStyle::PM_ExclusiveIndicatorHeight, &option);

        s.setHeight(qMax(s.height(), radioButtonHeight));
    }
    if (index.data(IsCheckRole).value<bool>()) {

        int checkButtonHeight = QApplication::style()->pixelMetric(QStyle::PM_ExclusiveIndicatorHeight, &option);

        s.setHeight(qMax(s.height(), checkButtonHeight));
    }

    if (index.data(IsPushButtonRole).value<bool>()) {

        int checkButtonHeight = QApplication::style()->pixelMetric(QStyle::PM_ExclusiveIndicatorHeight, &option);

        s.setHeight(qMax(s.height(), checkButtonHeight));
    }
    return s;
}



StoreItemTableView::StoreItemTableView(QWidget *parent)
        : QTableView(parent)
{
    setItemDelegate(new SelectButtonItemDelegate(this));

}
void StoreItemTableView::mousePressEvent(QMouseEvent *event)
{
    QModelIndex index = indexAt(event->pos());


    if (index.data(IsPushButtonRole).value<bool>()) {
        //switchButtonFlag(index);
        model()->setData(index,true,RadioSelectedRole);
        update(index);
        event->accept();
        return;

    }

    QTableView::mousePressEvent(event);
}

void StoreItemTableView::mouseReleaseEvent(QMouseEvent *event)
{
    QModelIndex index = indexAt(event->pos());
    if (index.data(IsRadioRole).value<bool>()) {
        switchButtonFlag(index);
        event->accept();
        return;

    }

    if (index.data(IsCheckRole).value<bool>()) {
        switchButtonFlag(index);
        event->accept();
        return;

    }

    if (index.data(IsPushButtonRole).value<bool>()) {
        model()->setData(index,false,RadioSelectedRole);
        update(index);
        event->accept();
        return;

    }

    QTableView::mouseReleaseEvent(event);
}

void StoreItemTableView::keyPressEvent(QKeyEvent *event)
{
    QModelIndex index = currentIndex();
    if(index.data(IsPushButtonRole).value<bool>()){
        if(event->key() == Qt::Key_Space){
            model()->setData(index,true,RadioSelectedRole);
            update(index);
            event->accept();
            return;
        }
        if(event->modifiers() == PANEL_MODIFIER && event->key() == PANEL_ENTER){
            model()->setData(index,true,RadioSelectedRole);
            update(index);
            event->accept();
            return;
        }
    }
    QTableView::keyPressEvent(event);
}

void StoreItemTableView::keyReleaseEvent(QKeyEvent *event)
{
    QModelIndex index = currentIndex();
    if(index.data(IsRadioRole).value<bool>()){
        if(event->key() == Qt::Key_Space){
            switchButtonFlag(index);
            event->accept();
            return;
        }
        if(event->modifiers() == PANEL_MODIFIER && event->key() == PANEL_ENTER){
            switchButtonFlag(index);
            event->accept();
            return;
        }
    }

    if(index.data(IsCheckRole).value<bool>()){
        if(event->key() == Qt::Key_Space){
            switchButtonFlag(index);
            event->accept();
            return;
        }
        if(event->modifiers() == PANEL_MODIFIER && event->key() == PANEL_ENTER){
            switchButtonFlag(index);
            event->accept();
            return;
        }
    }

    if(index.data(IsPushButtonRole).value<bool>()){
        if(event->key() == Qt::Key_Space){
            model()->setData(index,false,RadioSelectedRole);
            update(index);
            event->accept();
            return;
        }
        if(event->modifiers() == PANEL_MODIFIER && event->key() == PANEL_ENTER){
            //switchButtonFlag(index);
            model()->setData(index,false,RadioSelectedRole);
            update(index);
            event->accept();
            return;
        }
    }
    QTableView::keyReleaseEvent(event);


}
bool StoreItemTableView::event(QEvent *e)
{
        switch(e->type()){
        case QEvent::KeyPress:
        case QEvent::KeyRelease:
        {
            QKeyEvent *key = static_cast<QKeyEvent*>(e);
            if(key->modifiers() == PANEL_MODIFIER){
                if(e->type() == QEvent::KeyPress){
                    QKeyEvent *key = static_cast<QKeyEvent*>(e);
                    switch(key->key()){
                    case PANEL_UP:
                        selectUp();
                        return true;
                    case PANEL_LEFT:
                        selectLeft();
                        return true;
                    case PANEL_RIGHT:
                        selectRight();
                        return true;
                    case PANEL_DOWN:
                        selectDown();
                        return true;
                    default:
                        break;
                    }
                }else if(e->type() == QEvent::KeyRelease){
                    QKeyEvent *key = static_cast<QKeyEvent*>(e);
                    switch(key->key()){
                    case PANEL_UP:
                    case PANEL_LEFT:
                    case PANEL_RIGHT:
                    case PANEL_DOWN:
                        return true;
                    default:
                        break;
                    }
                }


                if(key->key() == PANEL_ENTER){
                    return QTableView::event(e);
                }else if(key->key() == PANEL_ESC){
                    return true;
                }else{
                    QApplication::sendEvent(p_GmainWin,e);
                }
            }else{
                if(e->type() == QEvent::KeyPress){
                    QKeyEvent *key = static_cast<QKeyEvent*>(e);
                    switch(key->key()){
                    case PANEL_UP:
                        selectUp();
                        return true;
                    case PANEL_LEFT:
                        selectLeft();
                        return true;
                    case PANEL_RIGHT:
                        selectRight();
                        return true;
                    case PANEL_DOWN:
                        selectDown();
                        return true;
                    default:
                        return QTableView::event(e);
                    }
                }else if(e->type() == QEvent::KeyRelease){
                    QKeyEvent *key = static_cast<QKeyEvent*>(e);
                    switch(key->key()){
                    case PANEL_UP:
                    case PANEL_LEFT:
                    case PANEL_RIGHT:
                    case PANEL_DOWN:
                        return true;
                    default:
                        return QTableView::event(e);
                    }
                }
            }
        }
           break;
        default:
            break;
        }

        return QTableView::event(e);
}

void StoreItemTableView::wheelEvent(QWheelEvent *e)
{
    if(e->modifiers() == PANEL_MODIFIER){
        if(e->angleDelta().y() > 0){
            focusPreviousChild();
        }else if(e->angleDelta().y() < 0){
            focusNextChild();
        }
    }
}


void StoreItemTableView::switchButtonFlag(QModelIndex &index)
{
    bool radioButtonSelected = index.data(RadioSelectedRole).value<bool>();
    model()->setData(index,!radioButtonSelected,RadioSelectedRole);
    update(index);
}
/*
 * 功能：
 *    将焦点移动到当前选中单元格的下边
 * 参数：
 *    无
 * 返回值：
 * 	  无
 */
void StoreItemTableView::selectDown()
{
    QModelIndex idx = currentIndex();
    int row = idx.row();
    int col = idx.column();

    do{
        if(row == (model()->rowCount() - 1)){
            row = 0;
        }else{
            ++row;
        }
    }while(!(idx.sibling(row,col).flags() & Qt::ItemIsSelectable));
    setCurrentIndex(idx.sibling(row,col));
}
/*
 * 功能：
 *    将焦点移动到当前选中单元格的上边
 * 参数：
 *    无
 * 返回值：
 * 	  无
 */
void StoreItemTableView::selectUp()
{
    QModelIndex idx = currentIndex();
    int row = idx.row();
    int col = idx.column();

    do{
        if(row == 0){
            row = model()->rowCount() -1 ;
        }else{
            --row;
        }
    }while(!(idx.sibling(row,col).flags() & Qt::ItemIsSelectable));
    setCurrentIndex(idx.sibling(row,col));
}
/*
 * 功能：
 *    将焦点移动到当前选中单元格的左边
 * 参数：
 *    无
 * 返回值：
 * 	  无
 */
void StoreItemTableView::selectLeft()
{
    QModelIndex idx = currentIndex();
    int row = idx.row();
    int col = idx.column();

    do{
        if(col == 0){
            col = model()->columnCount() - 1;
            if(row == 0)
            {
                row = model()->rowCount() - 1;
            }else{
                --row;
            }
        }else{
            --col;
        }
    }while(!(idx.sibling(row,col).flags() & Qt::ItemIsSelectable));
    setCurrentIndex(idx.sibling(row,col));
}
/*
 * 功能：
 *    将焦点移动到当前选中单元格的右边
 * 参数：
 *    无
 * 返回值：
 * 	  无
 */
void StoreItemTableView::selectRight()
{
    QModelIndex idx = currentIndex();
    int row = idx.row();
    int col = idx.column();

    do{
        if(col == (model()->columnCount() - 1)){
            col = 0;
            ++row;
            row %= model()->rowCount();
        }else{
            ++col;
        }
    }while(!(idx.sibling(row,col).flags() & Qt::ItemIsSelectable));
     setCurrentIndex(idx.sibling(row,col));
}
/*
 * 功能：
 *      选中一个单元格
 * 参数：
 *     int row:行, int col:列
 * 返回值：
 * 	  无
 */
void StoreItemTableView::select(int row, int col)
{

    int row_max = model()->rowCount();
    int col_max = model()->columnCount();

    if((row > row_max) || (col > col_max)
            || (row < 0) || (col <0)){
        return;
    }
    if(model()->index(row,col).flags() & Qt::ItemIsSelectable)
        setCurrentIndex(model()->index(row,col));

}
