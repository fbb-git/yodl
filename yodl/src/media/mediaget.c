#include "media.ih"

/*

    media_get is called by lget().

    It only inspects the CURRENT media, and returns the next available
    character. The current media may be a file, in which case the next
    character is read from the file (or EOF is returned), or a memory buffer,
    in which case the next character is returned from the memory buffer (or
    EOF if the terminating 0 is reached).

    By default the memory queue is inspected first. If nothing there, 
    then, IF a file is still available (mp->d_file returns true) then
    an attempt is made to retrieve from the file. 

*/

bool substActive = false;
int  nFileChars = 0;

int media_get(register Media *mp)
{
    register int ch = queue_get(&mp->d_queue);          // next waiting char

                                                        // No char:
    if ((mp->d_fgetc = (ch == EOF && mp->d_file)))      // read from file?
    {
        ch = fgetc(mp->d_file);                         // get char fm file
        if (ch == '\n')
            message_setlineno(++mp->d_lineno);
    }

    return ch;
}
