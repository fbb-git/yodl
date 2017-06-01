#include "lexer.ih"

void lexer_push_str(register Lexer *lp, char const *str)
{
    if (*str)
    {
        register Media *mp;

        /* max replacement exceed check removed in Yodl 4.00.00 */        

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
