#include "media.ih"

void l_media_push_front(register Media *mp, char const *txt)
{
    if (*txt)
        queue_push(&mp->d_queue, strlen(txt), txt);
}
