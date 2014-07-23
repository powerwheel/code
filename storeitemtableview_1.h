#ifndef GUI_RADIOBUTTONTABLEVIEW_H
#define GUI_RADIOBUTTONTABLEVIEW_H

#include <QTableView>
#include <QPushButton>
#include <QStyledItemDelegate>
#include <QRadioButton>
#include <QCheckBox>

class QMouseEvent;
class QKeyEvent;

static const int RadioSelectedRole = Qt::UserRole + 102;
static const int IsRadioRole = Qt::UserRole + 103;
static const int IsCheckRole = Qt::UserRole + 104;
static const int IsPushButtonRole = Qt::UserRole + 105;


class SelectButtonItemDelegate : public QStyledItemDelegate
{
public:
    SelectButtonItemDelegate(QObject *p);
    ~SelectButtonItemDelegate();

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    virtual QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;

private:
    void drawRadioButton(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const ;
    void drawCheckBox(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void drawPushButton(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    QPushButton *style_btn;
    QCheckBox *style_checkbox;
    QRadioButton *style_radiobutton;
};



class StoreItemTableView : public QTableView
{
public:
    StoreItemTableView(QWidget *parent);

    void selectLeft();
    void selectRight();
    void selectDown();
    void selectUp();
    void select(int row,int col);
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void wheelEvent(QWheelEvent *);
    bool event(QEvent *e);

private:
    void switchButtonFlag(QModelIndex &index);
    int m_iRow;
    int m_iColumn;

};

#endif
