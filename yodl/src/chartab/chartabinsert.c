#include "chartab.ih"

Result chartab_insert(HashMap *symtab,
                char const *name, char *table)
{
    return
        hashmap_insert
        (
            symtab,
            hashitem_new_destructor(CHARTABLE, name,
                                ct_construct(table), ct_destroy)
        );
}
