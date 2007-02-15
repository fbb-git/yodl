#include "parser.ih"

bool p_handle_unexpected_eof(register Parser *pp)
{
    message_show(MSG_EMERG);
    message(
        "%s: End of parameter list not found\n"
        "   EOF encountered. Offending parameterlist starts at\n"
        "   %s:%u",
        parser_fun(), pp->d_parlist_filename, (unsigned)pp->d_parlist_lineno);

    return false;                       /* Not reached, as MSG_EMERG exits  */
}
