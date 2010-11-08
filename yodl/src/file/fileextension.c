#include "file.ih"

char *file_extension(char const *path)
{
    register char *ext = f_dotExtension(path);

    return
        !ext++ || strlen(ext) == 0 ?            /* none found: return 0     */
            0
        :
            new_str(ext);                       /* or return the extension  */
}
