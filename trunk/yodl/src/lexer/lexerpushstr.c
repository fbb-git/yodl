#include "lexer.ih"

void lexer_push_str(register Lexer *lp, char const *str)
{
    if (*str)
    {
        register Media *mp;

        if 
        (
            lp->d_maxreplacements 
            && 
            ++lp->d_nreplacements >= lp->d_maxreplacements
        )
            l_max_replacements_exceeded(lp->d_maxreplacements);

        mp = lp->d_media_ptr;

        if (!mp || media_isFile(mp))
            l_push(lp, str, l_media_construct_memory);
        else
        {
            size_t length = strlen(str);

            if (isalpha(str[length - 1]) && isalpha(queue_peek(&mp->d_queue)))
                l_push(lp, str, l_media_construct_memory);
            else
                queue_push(&mp->d_queue, length, str);
        }
    }
}
