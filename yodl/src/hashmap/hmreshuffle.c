#include "hashmap.ih"

void hm_reshuffle(register HashMap *symtab)
{
    size_t newsize = symtab->d_size;
    size_t n;

    register HashItem **old = symtab->d_map;
    HashItem **new = new_calloc(newsize, sizeof(HashItem *));

    for (n = 0; n < symtab->d_n; old++)         /* visit all OLD elements   */
    {
                                                /* Got one                  */
        if (*old != (HashItem *)FREE && *old != (HashItem *)REMOVED)
        {
            size_t idx;
            if (hm_find(&idx, new, newsize, (*old)->d_key) == UFAILED)
                new[idx] = *old;
            n++;
        }
    }

    free(symtab->d_map);
    symtab->d_map = new;
}
