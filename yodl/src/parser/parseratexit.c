#include "parser.ih"

void parser_atexit(register Parser *pp, char *text)
{
    register StackValue stValue;

    stValue.u_charp = text;
    stack_push(&pp->d_atexit_st, stValue);
}
