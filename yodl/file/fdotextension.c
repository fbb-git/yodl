#include "file.ih"

char const *f_dotExtension(char const *path)
{
    register char const *slash = strrchr(path, '/');

    return strrchr(slash ? slash : path, '.');      /* find last .  */
}
