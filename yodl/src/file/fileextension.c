#include "file.ih"

char *file_extension(char const *path)
{
    register char *ext;
    register char *cp = strrchr(path, '/');

    ext = strrchr(cp ? cp : path, '.');         /* find last .              */

    return
        !ext || !strlen(ext + 1) ?              /* none found: return 0     */
            0
        :
            new_str(ext + 1);                   /* or return the extension  */
}
