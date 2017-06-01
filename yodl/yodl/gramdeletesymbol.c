#include "yodl.h"

void gram_DELETESYMBOL()
{
    parser_discard(&parser, SYMBOL, "DELETESYMBOL", "symbol");
}
