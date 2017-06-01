#include "hashmap.ih"

/* Returns idx to HashItem corresponding to  searched element or FAILED */

size_t hm_find_idx(register HashMap *map, char const *key, SymbolType type)
{
    size_t prime = map->d_size;
    size_t hashValue = hm_pjw(key) % prime;
    size_t idx;

    if (!hashValue)             /* make sure no initial hashvalue is 0,     */
        hashValue++;            /* as that invalidates add the hash rehash  */

    idx = hashValue;

    while (1)
    {
        register HashItem *atIdx = map->d_map[idx];

        switch (asHashmapValue(atIdx))
        {
            case FREE:
            return UFAILED;

            case REMOVED:
            break;

            case ACTIVE:
                if (hashitem_iskeytype(atIdx, key, type))
                    return idx;
            break;
        }
        idx = (idx + hashValue) % prime;    /* element in use: rehash */
    }
}
