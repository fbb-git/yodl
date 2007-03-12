#include "hashitem.ih"

bool hashitem_iskeytype(HashItem const *hashitem,
                            char const *key, SymbolType type)
{
    return (hashitem->d_type & type) && !strcmp(hashitem->d_key, key);
}
