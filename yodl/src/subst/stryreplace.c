#include "subst.ih"

SubstAction s_tryReplace(register Subst *sp)
{
    size_t nKeep = 1;               /* the new char already in the buffer   */
                                    /* if replacement encountered, return   */
                                    /* the replacement text                 */
    register char const *replacementText =     
                        s_state_replacement(sp->d_current_state_ptr, &nKeep);

    size_t length;
    char *buffer;

    if (replacementText == 0)       /* no replacement: done                 */
    {
        sp->d_nReplacements = 0;
        return SUBST_GETCHAR;
    }

    length = string_length(&sp->d_buffer);
    buffer = string_release(&sp->d_buffer);

    string_assign(&sp->d_buffer, replacementText);  /* store repl. text     */
                                                    /* and add the rest     */
    string_addstr(&sp->d_buffer, buffer + length - nKeep);
    free(buffer);

    if (++sp->d_nReplacements > sp->d_maxReplacements)
        s_maxReplacementsExceeded(sp->d_maxReplacements);

    
    return SUBST_REPLACED;
}





