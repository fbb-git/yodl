#include "yodl.h"

void gram_DELETEMACRO()
{
    parser_discard(&parser, MACRO, "DELETEMACRO", "macro");
}
