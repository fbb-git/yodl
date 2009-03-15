#include "file.ih"

void file_append(FILE *dest, char const *path)
{
    FILE *f = file_open(path, "r");
    file_copy2offset(dest, f, EOF);
    fclose(f);
}
