#include "media.ih"

void l_media_unget_memory(register Media *mp, int ch)
{
    queue_unget(&mp->d_queue, ch);
}
