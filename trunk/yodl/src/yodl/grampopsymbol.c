#include "yodl.h"

void gram_POPSYMBOL()
{
    parser_pop(&parser, SYMBOL, "POPSYMBOL", "symbol");
}
