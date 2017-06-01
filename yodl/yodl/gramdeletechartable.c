#include "yodl.h"

void gram_DELETECHARTABLE()
{
    register char *arg;
    register HashItem *item;

    parser_push_fun("DELETECHARTABLE");

    arg = parser_parlist(&parser, COLLECT_SET);

    item = hashmap_find(parser.d_symtab_ptr, arg, CHARTABLE);

    if (item == PFAILED)
    {
        if (message_show(MSG_ERR))
            message("DELETECHARTABLE: no character table `%s'", arg);
    }
    else if (chartab_find((char const **)hashitem_value(item)) == SUCCESS)
    {
        if (message_show(MSG_ERR))
            message(
                    "DELETECHARTABLE failed: character table `%s' is in use",
                    arg);
    }
    else
    {
        hashmap_erase(parser.d_symtab_ptr, arg, CHARTABLE);
        if (message_show(MSG_NOTICE))
            message("DELETECHARTABLE: `%s' discarded", arg);
    }

    parser_pop_fun();
    free(arg);
}
