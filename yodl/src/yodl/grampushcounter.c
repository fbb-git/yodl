#include "yodl.h"

/*
    Obtain the name of the counter to push, define it if it isn't
    defined yet.

    Then obtain the value of the counter, assign it to the counter
*/

void gram_PUSHCOUNTER()
{
    register char *name;
    register HashItem *item;
    char *arg;
    int value;
    Result res = SUCCESS;

    parser_push_fun("PUSHCOUNTER");

    name = parser_name_parlist(&parser,  true);
    item = hashmap_find(parser.d_symtab_ptr, name, COUNTER);
    arg  = parser_parlist(&parser, COLLECT_SET);

    if (!*arg)
        value = 0;
    else if ((res = parser_value(&parser, &value, arg)) == FAILED)
        if (message_show(MSG_ERR)) message(
            "PUSHCOUNTER: 2nd argument (`%s') must be empty, value or "
                                            "counter", arg);

    if (res == SUCCESS)
    {
        register StackValue stValue;

        stValue.u_int = value;
        if
        (
            (                       
                item != PFAILED &&  
                stack_push((Stack *)hashitem_value(item), stValue) == SUCCESS
            )
            ||                      
            counter_insert(parser.d_symtab_ptr, name, value) != FAILED
        )
        {
            if (message_show(MSG_NOTICE))
                message("PUSHCOUNTER %s (= %d)", string_short(name), value);
        }
        else if (message_show(MSG_ERR))
            message("PUSHCOUNTER: `%s' multiply defined", name);
    }

    parser_pop_fun();
    free(name);
    free(arg);
}
