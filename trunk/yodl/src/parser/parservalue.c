#include "parser.ih"

Result parser_value(register Parser *pp, int *value, char const *text)
{
                                                        /* find the counter */
    register HashItem *item = hashmap_find(pp->d_symtab_ptr, text, COUNTER);

    if (item != PFAILED)                                /* got it           */
    {
        *value = counter_value(item);                   /* assign the value */
        if (message_show(MSG_INFO))
            message("%s: counter[%s] == %d", parser_fun(), text, *value);
    }
    else if (sscanf(text, "%d", value) == 1)    /* convert text to number   */
    {
        if (message_show(MSG_INFO))
            message("%s: got value %d\n", parser_fun(),  *value);
    }
    else                                                    /* no number    */
    {
        if (message_show(MSG_ERR))
            message("%s: Number expected at `%s'", parser_fun(), text);
        return FAILED;
    }

    return SUCCESS;
}
