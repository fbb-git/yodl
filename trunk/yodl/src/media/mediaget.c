#include "media.ih"

/*

    media_get is called by lget().

    It only inspects the CURRENT media, and returns the next available
character. The current media may be a file, in which case the next character
is read from the file (or EOF is returned), or a memory buffer, in which case
the next character is returned from the memory buffer (or EOF if the
terminating 0 is reached).

*/

int media_get(register Media *mp)
{
    register int ch = queue_get(&mp->d_queue);

    if ((mp->d_fgetc = (ch == EOF && mp->d_file)))
    {
        ch = fgetc(mp->d_file);
        if (ch == '\n')
            message_setlineno(++mp->d_lineno);
    }

    return ch;
}
