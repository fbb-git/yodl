#include "subst.ih"

State *s_state_new()
{
    register State *sp = new_calloc(1, sizeof(State));

    string_construct(&sp->d_set, 0);
    sp->d_str = string_str(&sp->d_set);     /* locally avail. searchstring  */

    return sp;
}
