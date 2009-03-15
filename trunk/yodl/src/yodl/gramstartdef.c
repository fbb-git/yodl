#include "yodl.h"

void gram_STARTDEF()
{
    warning("STARTDEF() is deprecated. INCWSLEVEL() is used instead");
    gram_INCWSLEVEL();
}
