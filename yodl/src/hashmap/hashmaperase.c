#include "hashmap.ih"

Result hashmap_erase(register HashMap *map, char const *name, SymbolType type)
{
    register size_t idx = hm_find_idx(map, name, type);

    if (idx == UFAILED)
        return idx;

    hashitem_erase(map->d_map[idx]);
    map->d_map[idx] = (void *)REMOVED;
    map->d_n--;

    return SUCCESS;
}
