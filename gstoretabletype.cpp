#include "gstoretabletype.h"

GStoreTableType::GStoreTableType()
{
    m_type = InValid;
    m_bChecked = false;
    m_text = QString("");
    m_itemIdx = -1;
}

GStoreTableType::GStoreTableType(const GStoreTableType *t)
{
    m_type = t->type();
    m_text = t->text();
    m_bChecked = t->isChecked();
    m_itemIdx = t->itemIndex();
}
GStoreTableType::~GStoreTableType()
{

}
