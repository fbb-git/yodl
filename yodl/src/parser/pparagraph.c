#include "parser.ih"

static int s_nested = 0;

void p_paragraph(register Parser *pp, String const *sp)
{
    register HashItem *item;

    if
    (
        s_nested++
        ||
        (item = hashmap_find(pp->d_symtab_ptr, "PARAGRAPH", MACRO))
                                                            == PFAILED
    )
        (*pp->d_insert)(pp, string_str(sp));        /* no paragraph macro   */

    else if (!ostream_empty(pp->d_outs_ptr))
    {                                               /* get paragraph funct  */
        char const *def = macro_definition(hashitem_value(item));

        if (def == PFAILED)
        {
            if (message_show(MSG_ERR))
                message("MACRO PARAGRAPH': no expansion");
        }
        else
        {
            register void (*saved)(struct Parser *, char const *);
            register char *evaluated;

            HashItem *paragraph =
                    hashmap_find(pp->d_symtab_ptr, "XXparagraph", SYMBOL);

                                               /* See if we have a new par. */
            HashItem *parcount =
                    hashmap_find(pp->d_symtab_ptr, "XXwrotetext", COUNTER);

            if (paragraph != PFAILED)
                symbol_set(paragraph, string_str(sp));

            if (parcount != PFAILED)
                counter_set(parcount, 
                            (int)ostream_inserted_text(pp->d_outs_ptr));

            evaluated = parser_eval(pp, new_str(def));

            saved = parser_suppress_chartab(&parser);
            (*pp->d_insert)(pp, evaluated);
            pp->d_insert = saved;

            ostream_inserted_blanks(pp->d_outs_ptr);
            free(evaluated);
        }

    }
    s_nested--;
}
