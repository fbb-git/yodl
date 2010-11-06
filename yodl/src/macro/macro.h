#ifndef INCLUDED_MACRO_H_
#define INCLUDED_MACRO_H_

#include "../hashmap/hashmap.h"
#include "../stack/stack.h"

/* =========================================================================
    Macro holds the information about user defined macros
    processing nested files.

    Defining a macro means that its name is stored in the symboltable.
    If that succeeds, definitions and arguments may be defined.

    Renaming a macro means that the new name is stored in the symboltable
    and that the old name is removed from it. The new name will obtain as its
    symboltable-value the value of the old name.

    The symboltable holds indices into `macro'.
    Since Yodl doesn't run for extensive periods of time,
    removing a macro will not also shorten the corresponding
    macro's d_definition and d_arg structures. The appropriate elements,
    however, will be freed.

    functions are called macro_...()
*/
typedef struct
{
    Stack d_definition;     /* The definition stack: at a pushmacro */
                            /* a new definition will be pushed      */

    Stack d_arg;            /* Each macro has its own stack of      */
                            /* args. Local redefinitions of macros  */
                            /* may thus define a different number   */
                            /* of arguments.                        */
}
Macro;


Result      macro_insert(HashMap *map, char const *name,
                         char const *definition, size_t nargs);
Result      macro_pop(Macro *macro);

                            /* Always SUCCESS, but macro must be valid ptr  */
Result      macro_push(Macro *macro, char const *definition, size_t nargs);

static inline char const *macro_definition(Macro const *macro)
{
    return stack_tos(&macro->d_definition)->u_charCp;
}

static inline size_t macro_nArgs(Macro const *macro)
{
    return stack_tos(&macro->d_arg)->u_size_t;
}

#endif
