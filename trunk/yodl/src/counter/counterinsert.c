#include "counter.ih"

Result counter_insert(HashMap *symtab, char const *key, int value)
{
    return
        hashmap_insert
        (
            symtab,
            hashitem_construct(COUNTER, key, co_construct(value),
                                             stack_destroy)
        );
}
