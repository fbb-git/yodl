#include "parser.ih"

static char const *handlerName[] = 
{
    "COLLECT_SET",
    "DEFAULT_SET",
    "NOTRANS_SET",
    "IGNORE_SET",
    "NOEXPAND_SET",
    "SKIPWS_SET",
};
    
char const *p_handler(register Parser *pp)
{
    size_t idx = (pp->d_handler - ps_handlerSet[0]) / SIZEOF_TOKEN;

    return idx < SIZEOF_HANDLER_SET_ELEMENTS ? 
                handlerName[idx]
            :
                "UNKNOWN";
}
