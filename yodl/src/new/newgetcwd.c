#include "new.ih"
#include <stdio.h>

char *new_getcwd()
{
    char *cwd = getcwd(NULL, 0);

    if (cwd == NULL)
    {
        if (message_show(MSG_ALERT))
            message("Can't determine current working directory");
        out_of_memory();
    }
    
    register size_t length = strlen(cwd);   /* e.g. "x" -> 1            */

    if (cwd[length - 1] != '/')             /* true                     */
    {                                       /* true length: length + 1 
                                                due to ascii-Z          */
        new_size(&cwd, length + 2, length + 1, 1);

        cwd[length] = '/';                  /* replaces former ascii-Z  */
        cwd[length + 1] = 0;                /* writes final ascii-Z     */
    }

    return cwd;
}

        
