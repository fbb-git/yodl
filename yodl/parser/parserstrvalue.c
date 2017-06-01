#include "parser.ih"

char const *parser_strvalue(register Parser *pp, char const *txt)
{
    HashItem *it = hashmap_find(pp->d_symtab_ptr, txt, SYMBOL);

    return
        it != PFAILED ?
            symbol_value(it)
        :
            txt;
}
