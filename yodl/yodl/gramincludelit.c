/*
   gramINCLUDELIT.c Originally by Piet W. Plomp 10-Feb-97
   Implements the builtin macro INCLUDELIT

   Note: no attempt is made to find the file in the XXincludepath.
    Use PATHINCLUDELIT for that
 */

#include "yodl.h"

void gram_INCLUDELIT()
{
    warning("INCLUDELIT() is deprecated. NOEXPANDINCLUDE() is used instead");
    gram_NOEXPANDINCLUDE();
}
