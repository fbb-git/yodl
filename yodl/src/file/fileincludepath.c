#include "file.ih"

char const *file_includePath(HashMap *symtab)
{
    return symbol_value(hashmap_find(symtab, "XXincludePath", SYMBOL));
}
