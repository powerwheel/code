#ifndef GSTORETABLETYPE_H
#define GSTORETABLETYPE_H
#include <QString>
class GStoreTableType
{
public:
    GStoreTableType();
    ~GStoreTableType();

    GStoreTableType(const GStoreTableType *t);
    enum Type{
        InValid,
        Text,
        RadioButton,
        PushButton,
        Item
    };
    enum{
        ITEM_U = 1000,
        ITEM_I = 1001
    };

    inline void setType(GStoreTableType::Type type){ m_type = type;}
    inline GStoreTableType::Type type() const{ return m_type;}

    inline void setChecked(bool f){ m_bChecked = f; }
    inline bool isChecked() const{ return m_bChecked; }

    inline void setText(const QString &str){ m_text = str; }
    inline QString text()const { return m_text; }

    inline void setItemIndex(int idx){ m_itemIdx = idx; }
    inline int itemIndex()const { return m_itemIdx; }

private:
    QString m_text;
    bool m_bChecked;
    int m_itemIdx;
    Type m_type;
};

#endif // GSTORETABLETYPE_H
