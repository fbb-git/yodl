#include "hashmap.ih"

/* Returns pointer to HashItem corresponding to  searched element or PFAILED */

HashItem *hashmap_find(register HashMap *map, char const *key, SymbolType type)
{
    size_t idx = hm_find_idx(map, key, type);

    return idx == UFAILED ? PFAILED : map->d_map[idx];
}
