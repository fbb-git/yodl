#include "yodl.h"

void gram_UNDEFINEMACRO()
{
    warning("UNDEFINEMACRO() is deprecated. DELETEMACRO() is used instead");
    gram_DELETEMACRO();
}
