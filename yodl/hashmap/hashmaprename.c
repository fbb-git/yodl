#include "hashmap.ih"

HashItem *hashmap_rename(register HashMap *map, char const *name,
                                                char const *newName)
{
    register HashItem *item;

    size_t currentIdx = hm_find_idx(map, name, MACRO | BUILTIN);
    size_t newIdx;

    if (currentIdx == UFAILED)
        return PFAILED;

    if (hm_find(&newIdx, map->d_map, map->d_size, newName) != UFAILED)
        return 0;

    hashitem_changekey(item = map->d_map[currentIdx], newName);

    map->d_map[newIdx] = item;
    map->d_map[currentIdx] = (void *)REMOVED;

    return item;
}
