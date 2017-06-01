#include "media.ih"

void media_destructor(register void *mp)
{
    if (((Media *)mp)->d_file)
        fclose(((Media *)mp)->d_file);

    queue_destruct(&((Media *)mp)->d_queue);
    free(((Media *)mp)->d_filename);
    free(mp);
}
