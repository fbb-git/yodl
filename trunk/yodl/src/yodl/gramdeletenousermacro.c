#include "yodl.h"

void gram_DELETENOUSERMACRO()
{
    parser_discard(&parser, NOUSERMACRO, "DELETENOUSERMACRO", "nousermacro");
}
