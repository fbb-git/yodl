#include "builtin.ih"

void builtin_insert(HashMap *symtab, Builtin *builtin)
{
    while (builtin->d_name)
    {
        hashmap_insert
        (
            symtab,
            hashitem_construct(BUILTIN, builtin->d_name, builtin, root_nop)
        );
        builtin++;
    }
}
