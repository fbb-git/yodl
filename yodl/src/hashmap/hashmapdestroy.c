#include "hashmap.ih"

void hashmap_destroy(register HashMap *map)
{
    for (; map->d_size--; )
    {
        if (map->d_map[map->d_size])
        {
            hashitem_erase(map->d_map[map->d_size]);
            free(map->d_map[map->d_size]);
        }
    }
    free(map->d_map);
}
