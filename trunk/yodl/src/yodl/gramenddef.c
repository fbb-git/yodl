#include "yodl.h"

void gram_ENDDEF()
{
    warning("ENDDEF() is deprecated. DECWSLEVEL() is used instead");
    gram_DECWSLEVEL();
}
