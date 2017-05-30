#include "subst.ih"

/*
    if ch is not EOF and found in the current state transition, then add
    it to the buffer holding the matched characters (so far).

    If there isn't a match, but if there is a replacement, then put the
    replacement into the buffer.

    If there isn't a match, but there was a match earlier, then put the
    earlier replacement and all later characters into the buffer, and indicate
    a substitution as well
*/

SubstAction subst_process(register Subst *sp, int ch)
{
                 /* calls either s_noSubst or s_subst */
    return (*sp->d_action) (sp, ch);
}
