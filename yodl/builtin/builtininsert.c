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

/*
    yodl/pramble -> builtin_insert. The table is builtin_array, defined in 
    (from here:) ../../tmp/wip/builtins.def.

    That table merely associates builtin function names with builtin
    functions. 
*/

