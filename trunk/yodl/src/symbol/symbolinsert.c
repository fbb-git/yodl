#include "symbol.ih"

Result symbol_insert(HashMap *symtab, char const *name, char const *value)
{
    return
        hashmap_insert
        (
            symtab,
            hashitem_construct(SYMBOL, name, sy_construct(value),
                                                stack_destroy)
        );
}
