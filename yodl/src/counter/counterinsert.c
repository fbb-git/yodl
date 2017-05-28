#include "counter.ih"

Result counter_insert(HashMap *symtab, char const *key, int value)
{
    return
        hashmap_insert
        (
            symtab,
            hashitem_new_destructor(COUNTER, key, co_construct(value),
                                             stack_destruct)
        );
}
