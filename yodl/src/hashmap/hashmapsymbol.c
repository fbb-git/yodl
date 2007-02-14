#include "hashmap.ih"

/* returns type of symbol at map[idx]. idx must be valid */

SymbolType hashmap_symboltype(register HashMap *map, size_t idx)
{
    return hashitem_type(map->d_map[idx]);
}
