#include "lexer.ih"

void l_media_construct_file(register Media *mp, register Lexer *lp,
                            char const *pathname)
{
    /*
        *mp is initialized to 0, so the queue is 0 as well: ok, since the
        queue's destructor can handle that
    */
    mp->d_isfile = true;

    if (++lp->d_filedepth > lp->d_maxdepth)
        if (message_show(MSG_CRIT))
            message("Max number of nested files (%u) exceeded at\n"
                            "`%s'", (unsigned)lp->d_maxdepth, pathname);


    if (!pathname || !strcmp(pathname, "-"))    /* no name, so it's stdin   */
    {
        mp->d_filename = new_str("stdin");
        mp->d_file = stdin;
        message_setfilename("<stdin>");
    }
    else
    {
        mp->d_filename = new_str(pathname);
        mp->d_file = file_open(pathname, "r");
        message_setfilename(pathname);
        message_setlineno(mp->d_lineno = 1);
    }
    queue_construct(&mp->d_queue, "");
    if (message_show(MSG_INFO))
        message("New file media.");
}



