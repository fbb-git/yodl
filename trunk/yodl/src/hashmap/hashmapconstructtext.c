#include "hashmap.ih"

void hashmap_constructText(HashMap *map, char const *(*ptr)[2])
{
    hashmap_construct(map);

    while ((*ptr)[0])
    {
        hashmap_insert
        (
            map,
            hashitem_construct(CHARPTR, (*ptr)[0], new_str((*ptr)[1]), free)
        );
        ptr++;
    }
}
