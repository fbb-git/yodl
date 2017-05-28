#include "symbol.ih"

Result symbol_insert(HashMap *symtab, char const *name, char const *value)
{
    return
        hashmap_insert
        (
            symtab,
            hashitem_new_destructor(SYMBOL, name, sy_construct(value),
                                                stack_destruct)
        );
}
