#include "parser.ih"

int parser_data = 0;                /* to ensure linkage via argsconstruct.c */

Stack   ps_fun_st;                  /* stores the names of functions    */

                                    /* zeroed by the compiler */
bool (*ps_handlerSet[SIZEOF_HANDLER_SET_ELEMENTS][SIZEOF_TOKEN])(Parser *);
