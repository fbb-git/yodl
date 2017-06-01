#include "lexer.ih"

void l_media_construct_memory(register Media *mp, register Lexer *lp,
                              char const *str)
{
    mp->d_isfile = false;
    mp->d_filename = new_str(lexer_filename(lp));
    mp->d_lineno = lexer_lineno(lp);
    queue_construct(&mp->d_queue, str);

    if (message_show(MSG_INFO))
        message("New memory media. Q at %p", &mp->d_queue);
}
