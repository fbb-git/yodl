#include "yodl.h"

/*
    Standard includepath is .:STD_INCLUDE

    If a new path is specified, it replaces the standard. So the caller is
    responsible for adding `.', but also has the freedom not to use `.'

    If the -I flag is not specified, then the environment variable
    YODL_INCLUDE_PATH is interrogated. If it contains a text, then that text
    is used as the include path. Otherwise the standard includepath is used.

    If the pathsetting used with -I or the YODL_INCLUDE_PATH environment
    variable contains $STD_INCLUDE then the standard include path (except for
    the .: setting) is used at that location in the include path.
*/

                                            /* put XXincludePath in symtab */
void insert_XXincludePath()
{
    char const *arg = args_optarg('I');
    char *allocated = 0;

    if (!arg)
        arg = getenv("YODL_INCLUDE_PATH");

    if (!arg)
        arg = ".:" STD_INCLUDE;         /* "." TOPLEVEL_VERSION; */
    else
    {
        allocated = string_str_replace(arg, "$STD_INCLUDE", STD_INCLUDE);
        arg = allocated;
    }

    char *refined = refine_XXincludePath(arg);
    free(allocated);

    if 
    (
        symbol_insert(&symtab, "XXincludePath", refined) != FAILED
        &&
        message_show(MSG_NOTICE)
    )
        message("Include path: `%s'", refined);

    free(refined);
}
