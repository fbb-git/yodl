#include "hashmap.ih"

/* Returns idx to HashItem corresponding to  searched element or FAILED */

unsigned hm_find_idx(register HashMap *map, char const *key, SymbolType type)
{
    unsigned prime = map->d_size;
    unsigned hashValue = hm_pjw(key) % prime;
    unsigned idx;

    if (!hashValue)             /* make sure no initial hashvalue is 0,     */
        hashValue++;            /* as that invalidates add the hash rehash  */

    idx = hashValue;

    while (1)
    {
        register HashItem *atIdx = map->d_map[idx];

        switch ((unsigned)atIdx)
        {
            case FREE:
            return FAILED;

            case REMOVED:
            break;

            default:
                if (hashitem_iskeytype(atIdx, key, type))
                    return idx;
            break;
        }
        idx = (idx + hashValue) % prime;    /* element in use: rehash */
    }
}
