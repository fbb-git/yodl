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

SubstAction subst_action(register Subst *sp, int ch)
{
    size_t n_keep;
    register char const *text;
                                            /* char found in the current    */
    if                                      /*                      state ? */
    (
        ch != EOF                           /* if not an EOF char           */
        &&                                  /* and if state transition      */
        s_state_transition((State **)(void *)&sp->d_current_state_ptr, ch)
    )
    {                                       /* add char to `matched so far' */
        string_addchar(&sp->d_buffer, ch);  
        return SUBST_CONTINUE;
    }

    n_keep = 0;                                     /* replacement seen ?   */

    if ((text = s_state_replacement(sp->d_current_state_ptr, &n_keep)))
    {
        size_t length = string_length(&sp->d_buffer);
        char *buffer = string_release(&sp->d_buffer);

        string_assign(&sp->d_buffer, text);
        string_addstr(&sp->d_buffer, buffer + length - n_keep);
        free(buffer);
    }

    if (ch != EOF)
        string_addchar(&sp->d_buffer, ch);

    return text == 0 ? SUBST_GETCHAR : SUBST_SUBSTITUTION;
}
