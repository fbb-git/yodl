#ifndef _INCLUDED_ROOT_H_
#define _INCLUDED_ROOT_H_

#define MAX_LINE_LENGTH (1000)

typedef enum
{
    false = 0,
    true  = 1
}
bool;

typedef enum
{
    SUCCESS = 0,
    FAILED = ~0,
}
Result;

#define PFAILED     ((void *)FAILED)

typedef enum
{
    UNDEFINED_SYMBOL   = 0,
    BUILTIN     = 1 << 0,
    CHARTABLE   = 1 << 1,
    COUNTER     = 1 << 2,
    MACRO       = 1 << 3,
    NOUSERMACRO = 1 << 4,
    SYMBOL      = 1 << 5,

    CHARPTR     = 1 << 6,               /* used by hashmap_constructText()  */
    VOIDPTR     = 1 << 7,               /* for the postprocessors           */

    ANY         = (1 << 16) - 1,        /* Define at most 16 different      */
                                        /* SymbolTypes.                     */
#if 0
    PARLIST_EVAL    = 1 << 16,          /* Recognize EVAL() in parlists     */
    PARLIST_SWALLOW = 1 << 17,          /* NOTRANS, NOEXPAND in parlists    */
                                        /* have their parlist swallowed     */
                                        /* without further interpretation   */
#endif
    NOEXPAND_EXEC   = 1 << 18,          /* except for builtins showing this */
                                        /* flag                             */
}
SymbolType;

void out_of_memory();
char *new_str(char const *str);
void root_nop(void *);                  /* do nothing                       */

#endif
