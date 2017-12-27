#include "parser.ih"

void p_compute(register Parser *pp, Term *term)
{
    register HashItem *item =                           // check for counters
                        hashmap_find(pp->d_symtab_ptr, term->text, COUNTER);

    if (item != PFAILED)                                /* got it           */
    {
        term->value = counter_value(item);              /* assign the value */
        if (message_show(MSG_INFO))
            message("%s: counter[%s] == %d", parser_fun(), term->text, 
                                                           term->value);
    }
    else if (sscanf(term->text, "%d", &term->value) == 1)   // no counter, so
    {                                                       // a number req'd
        if (message_show(MSG_INFO))
            message("%s: got value %d\n", parser_fun(),  term->value);
    }
    else                                                    /* no number    */
    {
        if (message_show(MSG_ERR))
            message("%s: Number expected at `%s'", parser_fun(), term->text);
        term->result = FAILED;
        return;
    }

    term->result = SUCCESS;
}

