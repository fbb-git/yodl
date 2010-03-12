#include "hashmap.ih"

void hashmap_construct(register HashMap *map)
{
    memset(map, 0, sizeof(HashMap));
    map->d_prime_idx = 0;
    hm_expand(map);
}
