#include "subst.ih"

char const *s_state_replacement(register State const *sp,
                                        register size_t *n_back)
{
    register char const *text;

    while (true)
    {
        if ((text = sp->d_replacement))
            return text;

        if (!(sp = sp->d_parent))
            return 0;

        ++*n_back;
    }
}
