#include "hashitem.ih"

SymbolType hashitem_type(register HashItem *item)
{
    return item == PFAILED ? UNDEFINED_SYMBOL : (item->d_type & ANY);
}
