#include "parser.ih"

Stack   ps_fun_st;                  /* stores the names of functions    */

bool (*ps_handlerSet[SIZEOF_HANDLER_SET_ELEMENTS][SIZEOF_TOKEN])(Parser *) = {};
