#include "media.ih"

void media_save_state(register Media *mp)
{
    if (!media_isFile(mp))                    /* no file: push Media  */
    {
        if (message_show(MSG_INFO))
            message("Pushing queue %p", &mp->d_queue);
    }
    else
    {                                           /* it's a file: set its */
        long offset = m_set_offset(mp);   /* offset, and close it */
        if (message_show(MSG_INFO))
            message("Pushing file at offset %ld", offset);
        fclose(m_file(mp));
    }
}
