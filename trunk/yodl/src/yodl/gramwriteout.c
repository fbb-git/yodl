#include "yodl.h"

void gram_WRITEOUT()
{
    warning("WRITEOUT() is deprecated. FPUTS() is used instead");
    gram_FPUTS();
}
