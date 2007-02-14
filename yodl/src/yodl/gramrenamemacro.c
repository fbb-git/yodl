#include "yodl.h"

void gram_RENAMEMACRO()
{
    char *currentName;
    char *newName;

    parser_push_fun("RENAMEMACRO");

    currentName = parser_name_parlist(&parser,  true);
    newName = parser_name_parlist(&parser,  false);

    switch
    (
        (size_t)hashmap_rename(parser.d_symtab_ptr, currentName, newName)
    )
    {
        case (size_t)PFAILED:
            if (message_show(MSG_ERR))
                message("RENAMEMACRO `%s': Unknown macro/builtib",
                            currentName);
        break;

        case 0:
            if (message_show(MSG_ERR))
                message("RENAMEMACRO `%s' to `%s': `%s' already in use",
                        currentName, newName, newName);
        break;

        default:
            if (message_show(MSG_NOTICE))
                message("RENAMEMACRO `%s' to `%s'", currentName, newName);
        break;
    }
    parser_pop_fun();
    free (currentName);
    free (newName);
}
