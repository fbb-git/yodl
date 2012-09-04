#include "new.ih"

char *new_getcwd()
{
    char *cwd = getcwd(NULL, 0);

    if (cwd == NULL)
    {
        if (message_show(MSG_ALERT))
            message("Can't determine current working directory");
        out_of_memory();
    }
    
    size_t length = strlen(cwd);
    if (cwd[length - 1] != '/')
    {
        cwd[length] = '/';
        cwd[length + 1] = 0;
    }
    return cwd;
}

        
