#include "yodl.h"

char *refine_XXincludePath(char const *path)
{
    char *local_path = new_str(path);
    char *path_element = strtok(local_path, ":");
    String result;
    char *ret;

    string_construct(&result, NULL);

    while (path_element)
    {
        if (strchr("./", *path_element) == NULL)
        {
            string_addstr(&result, args_initial_dir());
            string_addcharOnce(&result, '/');
        }

        string_addstr(&result, path_element);

        if (!(path_element = strtok(NULL, ":")))
            break;

        string_addchar(&result, ':');
    }
     
    ret = new_str(string_str(&result));
    string_destroy(&result);

    return ret;
}




