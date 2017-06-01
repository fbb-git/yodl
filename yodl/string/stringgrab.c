#include "string.ih"

char *string_grab(register String **sp)
{
    register char *ret = string_release(*sp);

    free(*sp);
    *sp = 0;

    return ret;
}
