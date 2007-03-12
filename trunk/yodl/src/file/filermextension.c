#include "file.ih"

char *file_rmExtension(char const *path)
{
    register char *ext;
    register char *cp = strrchr(path, '/');

    ext = strrchr(cp ? cp : path, '.');         /* find last .              */

    if (!ext)                                   /* none found: return path  */
        return new_str(path);

    cp = new_str(path);                         /* copy the path            */
    cp[ext - path] = 0;                         /* cut at the last .        */

    return cp;
}
