#include "hashmap.ih"

HashItem *hashmap_rename(register HashMap *map, char const *name,
                                                char const *newName)
{
    register HashItem *item;

    unsigned currentIdx = hm_find_idx(map, name, MACRO | BUILTIN);
    unsigned newIdx;

    if (currentIdx == FAILED)
        return PFAILED;

    if (hm_find(&newIdx, map->d_map, map->d_size, newName) != FAILED)
        return 0;

    hashitem_changekey(item = map->d_map[currentIdx], newName);

    map->d_map[newIdx] = item;
    map->d_map[currentIdx] = (void *)REMOVED;

    return item;
}
