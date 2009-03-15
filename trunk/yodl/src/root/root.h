#ifndef INCLUDED_ROOT_H_
#define INCLUDED_ROOT_H_

/* 
    See 
    http://www.gnu.org/software/libc/manual/html_node/Feature-Test-Macros.html
    for a rationale behind the following #define:
    
*/
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include <stddef.h>

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
    FAILED = ~0
}
Result;

#define PFAILED     ((void *)FAILED)
#define UFAILED     ((size_t)FAILED)

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
    NOEXPAND_EXEC   = 1 << 18           /* except for builtins showing this */
                                        /* flag                             */
}
SymbolType;

void out_of_memory(void);
char *new_str(char const *str);
void root_nop(void *);                  /* do nothing                       */

/* GCC version checking borrowed from glibc. */
#if defined(__GNUC__) && defined(__GNUC_MINOR)
#  define GNUC_PREREQ(maj,min) \
        ((__GNUC__ << 16) + __GNUC_MINOR__ >= ((maj) << 16) + (min))
#else
#  define GNUC_PREREQ(maj,min) 0
#endif

/* Does this compiler support format string checking? */
#if GNUC_PREREQ(2,0)
#  define ATTRIBUTE_FORMAT_PRINTF(a,b) \
        __attribute__ ((__format__ (__printf__, a, b)))
#else
#  define ATTRIBUTE_FORMAT_PRINTF(a,b)
#endif

/* va_copy is C99; try to deal with systems that lack it. */
#ifndef va_copy
#  ifdef __va_copy
#    define va_copy __va_copy
#  else
#    define va_copy(dest, src) do { dest = src; } while (0)
#  endif
#endif

#endif
