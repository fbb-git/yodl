#include "parser.ih"

void parser_atexit(register Parser *pp, char *text)
{
    stack_push(&pp->d_atexit_st, text);
}
