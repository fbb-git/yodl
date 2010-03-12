#include "hashitem.ih"

HashItem *hashitem_construct(SymbolType type, char const *key, void *value,
                                         void (*destructor)(void *))
{
    register HashItem *ret = hashitem_new(key, type);
    hashitem_set(ret, value, destructor);

    return ret;
}
