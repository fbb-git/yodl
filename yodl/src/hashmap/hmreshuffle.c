#include "hashmap.ih"

void hm_reshuffle(register HashMap *symtab)
{
    unsigned newsize = symtab->d_size;
    unsigned n;

    register HashItem **old = symtab->d_map;
    HashItem **new = new_calloc(newsize, sizeof(HashItem *));

    for (n = 0; n < symtab->d_n; old++)         /* visit all OLD elements   */
    {
                                                /* Got one                  */
        if (*old != (HashItem *)FREE && *old != (HashItem *)REMOVED)
        {
            unsigned idx;
            if (hm_find(&idx, new, newsize, (*old)->d_key) == FAILED)
                new[idx] = *old;
            n++;
        }
    }

    free(symtab->d_map);
    symtab->d_map = new;
}
