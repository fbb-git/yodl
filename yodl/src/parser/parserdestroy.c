#include "parser.ih"

void parser_destroy(register Parser *pp)
{
    stack_destroy(&pp->d_paren_st);
    free(pp->d_parlist_filename);

    stack_destroy(&pp->d_ws_level_st);
    
}
