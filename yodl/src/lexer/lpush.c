#include "lexer.ih"

void l_push(register Lexer *lp, char const *info,
                       void (*constructor)(Media *, Lexer *, char const *))
{
    register Media *media = new_calloc(1, sizeof(Media));

    if (lp->d_media_ptr)
        l_media_save_state(lp->d_media_ptr);    /* info and close/save  */
                                                /* info about current   */
                                                /* file (if any)        */

    (*constructor)(media, lp, info);            /* construct new media  */
                                                /* generates MSG_INFO   */

    stack_push(&lp->d_media_st, media);         /* push new media info  */
    lp->d_media_ptr = media;                    /* set tos pointer      */

    lp->d_lastchar = 0;                         /* something pushed, so */
                                                /* end an EOF condition */
}
