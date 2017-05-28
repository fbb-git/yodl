#include "builtin.ih"

void builtin_insert(HashMap *symtab, Builtin *builtin)
{
    while (builtin->d_name)
    {
        hashmap_insert
        (
            symtab,
            hashitem_new_destructor(BUILTIN, builtin->d_name, builtin, root_nop)
        );
        builtin++;
    }
}
