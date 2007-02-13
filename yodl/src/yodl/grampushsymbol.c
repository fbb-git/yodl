#include "yodl.h"

void gram_PUSHSYMBOL()
{
    register char *name;
    register HashItem *item;
    register StackValue stValue;

    parser_push_fun("PUSHSYMBOL");

    name = parser_name_parlist(&parser,  true);
    stValue.u_charp  = parser_parlist(&parser, COLLECT_SET);
    item = hashmap_find(parser.d_symtab_ptr, name, SYMBOL);

    if
    (
        (
            item != PFAILED
            &&
            stack_push((Stack *)hashitem_value(item), stValue) == SUCCESS
        )
        ||
        symbol_insert(parser.d_symtab_ptr, name, stValue.u_charp) != FAILED
    )
    {
        if (message_show(MSG_NOTICE))
            message("PUSHSYMBOL %s (= %s)", name, 
                                            string_short(stValue.u_charp));
    }
    else if (message_show(MSG_ERR))
        message("PUSHSYMBOL: `%s' multiply defined", name);

    parser_pop_fun();
    free (name);
}
