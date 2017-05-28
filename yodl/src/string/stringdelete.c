#include "string.ih"

void string_delete(register String **sp)
{
    string_destruct(*sp);
    free(*sp);
    *sp = 0;
}
