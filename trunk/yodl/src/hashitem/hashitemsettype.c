#include "hashitem.ih"

void hashitem_setType(register HashItem *item, SymbolType type)
{
    item->d_type = type;
}
