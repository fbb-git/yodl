#include "macro.ih"

Result macro_insert(HashMap *symtab,
                char const *name, char const *definition, size_t nargs)
{
    return
        hashmap_insert
        (
            symtab,
            hashitem_construct(MACRO, name, mc_construct(definition, nargs),
                                            mc_destroy)
        );
}
