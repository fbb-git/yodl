#include "hashmap.ih"

/*  returns idx of inserted element or FAILED, if already inserted */

Result hashmap_insert(register HashMap *map, register HashItem *hashitem)
{
    size_t idx;

    if (map->d_n * 100 > map->d_size * 70)
        hm_expand(map);

    if
    (
        hm_find(&idx, map->d_map, map->d_size,
                                hashitem_key(hashitem)) == UFAILED
    )
    {
        map->d_map[idx] = hashitem;
        map->d_n++;

        return idx;
    }
    return FAILED;
}
