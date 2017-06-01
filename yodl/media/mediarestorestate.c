#include "media.ih"

void media_restore_state(register Media *mp)
{
    char const *filename = media_filename(mp);

    message_setfilename(filename);
    message_setlineno(mp->d_lineno);

    if (!mp->d_file)                           /*  switch to memory buffer */
    {
        if (message_show(MSG_INFO))
            message("Reactivating queue %p", mp->d_queue);
        return;
    }
                                                /* switch back to file      */
    mp->d_file = file_open(filename, "r");      /* read the file            */

                                                /* go to its offset         */
    if (fseek(mp->d_file, mp->d_offset, SEEK_SET) != 0)
        if (message_show(MSG_ALERT))
            message("Can't continue at line %u (offset `%ld')",
                (unsigned)mp->d_lineno, mp->d_offset);

    if (message_show(MSG_INFO))
        message("Continuing at line %z (offset %ld, d_queue = %p)",
                      (unsigned)mp->d_lineno, mp->d_offset, &mp->d_queue);
}
