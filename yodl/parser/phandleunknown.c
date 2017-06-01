#include "parser.ih"

bool p_handle_unknown(register Parser *pp)
{
    message_show(MSG_EMERG);
    message("%s: unknown token", parser_fun());

    return false;       /* not reached, MSG_EMERG exits     */
}
