#include "file.ih"

char *f_search_path(char const *request, String *fname, char const *path)
{
    char *local_path = new_str(path);
    char *path_element = strtok(local_path, ":");
    char *ret = NULL;

    while (path_element)
    {
        Result result;
        String currentName;

        if (message_show(MSG_NOTICE))
            message("Trying to open `%s/%s'", path_element, request);

        if (*path_element != '.')           /* not relative path element */
            string_construct(&currentName, path_element);
        else
        {
            char *cp = new_getcwd();
            string_construct(&currentName, cp);
            free(cp);
            string_addstr(&currentName, path_element);
        }

        f_fullname(&currentName, fname);
        result = f_opt_extension(&currentName);
        ret = new_str(string_str(&currentName));
        string_destroy(&currentName);

        if (result == SUCCESS)
        {
            if (message_show(MSG_INFO))
                message("File `%s' is read as `%s'", request, ret);
            break;
        }

        if (message_show(MSG_NOTICE))
            message("File `%s' is not found as `%s[%s]'",
                                        request, ret, DEFAULT_EXT);
        free(ret);
        if (!(path_element = strtok(NULL, ":")))
        {
            if (message_show(MSG_NOTICE))
                message("Can't find `%s[%s]'", request, DEFAULT_EXT);
            ret = NULL;
        }
    }

    free(local_path);
    string_destroy(fname);

    return ret;
}
