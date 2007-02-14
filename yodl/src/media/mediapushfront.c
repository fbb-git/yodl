#include "media.ih"

void media_push_front(register Media *mp, char const *txt)
{
    if (*txt)
        queue_push(&mp->d_queue, strlen(txt), txt);
}
