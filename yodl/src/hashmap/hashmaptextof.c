#include "hashmap.ih"

char const *hashmap_textOf(register HashMap *map, char const *key)
{
    unsigned idx = hm_find_idx(map, key, ANY);

    return (idx == UFAILED) ?
                ""
            :
                (char const *)hashitem_value(map->d_map[idx]);
}
