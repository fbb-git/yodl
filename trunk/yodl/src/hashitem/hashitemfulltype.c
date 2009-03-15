#include "hashitem.ih"

SymbolType hashitem_fullType(register HashItem *item)
{
    return item == PFAILED ? UNDEFINED_SYMBOL : item->d_type;
}
