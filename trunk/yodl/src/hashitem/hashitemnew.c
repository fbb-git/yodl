#include "hashitem.ih"

HashItem *hashitem_new(char const *key, SymbolType type)
{
    HashItem *ret = new_calloc(1, strlen(key) + sizeof(HashItem));

    ret->d_key = new_str(key);
    ret->d_type = type;

    return ret;
}
