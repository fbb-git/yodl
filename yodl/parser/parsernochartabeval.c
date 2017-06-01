#include "parser.ih"

char *parser_nochartab_eval(register Parser *pp, register char *arg)
{
    if (chartab_use(parser.d_symtab_ptr, "", true) == SUCCESS)
    {
        parser_apply_chartab(&parser);
        arg = parser_eval(pp, arg);
        chartab_pop();
        parser_apply_chartab(&parser);
    }
    return arg;
}
