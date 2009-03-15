#include "yodl.h"

void gram_DELETECOUNTER ()
{
    parser_discard(&parser, COUNTER, "DELETECOUNTER", "counter");
}
