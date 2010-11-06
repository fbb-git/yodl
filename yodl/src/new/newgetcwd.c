#include "new.ih"

char *new_getcwd()
{
    char *cwd =  n_malloc(PATH_MAX + 1);

    if (!getcwd(cwd, PATH_MAX) && message_show(MSG_ALERT))
            message("Can't determine current working directory");
    
    size_t length = strlen(cwd);
    if (cwd[length - 1] != '/')
    {
        cwd[length] = '/';
        cwd[length + 1] = 0;
    }
    return cwd;
}

        
