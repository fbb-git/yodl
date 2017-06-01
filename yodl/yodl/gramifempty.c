
#include "yodl.h"

void gram_IFEMPTY()
{
    parser_if_cond(&parser, parser_if_empty, "IFEMPTY", 3);
}
