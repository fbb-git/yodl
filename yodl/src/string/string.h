#ifndef _INCLUDED_STRING_H_
#define _INCLUDED_STRING_H_

/*
    String stores ascii-Z strings. Char * args may be NULL.

    string_format() assumes C99 is active (see the snprintf() manpage)
*/

#include "../root/root.h"

#include <stdarg.h>
#include <string.h>

typedef struct
{
    size_t d_size;        /* buffer size of d_str */
    size_t d_length;      /* not counting ascii-Z */
    char *d_str;
}
String;

void        string_add(String *dest, String *src);
void        string_addchar(String *sp, int c);  /* actually: c is a char */
void        string_additerators(String *string, char const *begin,
                                                char const *end);
void        string_addstr(String *sp, char const *str);
void        string_assign(String *sp, char const *str);
void        string_construct(String *sp, char const *init);
void        string_copy(String *dest, String *src);
size_t      string_count(String *sp, char needle);
void        string_destroy(String *sp);             /* invalidates sp       */
void        string_destructor(void *sp);            /* frees sp + contents  */
void        string_erase(String *sp);               /* resets to ""         */
void        string_fill(String *s, size_t length, int fill);
                                            /* FAILED if no such character */
size_t      string_find_first_of(String *sp, char const *accept);
size_t      string_find_first_not_of(String *sp, int (*fun)(int));
char       *string_firstword(char **str);           /* returns new string   */
                                                    /* or NULL if none      */
                                                    /* *str points beyond   */
                                            /* assigns new contents         */
void        string_format(String *sp, char const *fmt, ...)
            ATTRIBUTE_FORMAT_PRINTF(2, 3);
size_t      string_length(String const *sp);
String     *string_new(char const *initext);
char        string_popfront(String *sp);
char       *string_release(String *sp);     /* returns interal str          */
                                            /* don't use sp anymore.        */
                                            /* destroy/uctor isn't required */
                                            /* (but can still be used)      */

void        string_replace(String *sp, char const *srch, char const *replace);
                                            /* allocates and formats        */
                                            /* returned string. size (incl. */
                                            /* ascii-Z) in n                */
char       *string_str_replace(char const *cp,
                                    char const *srch, char const *replace);
                                            /* allocates and formats        */
                                            /* returned string. size (incl. */
                                            /* ascii-Z) in n                */
char       *string_vformat(size_t *n, char const *fmt, va_list list)
            ATTRIBUTE_FORMAT_PRINTF(2, 0);

void        string_swallow(String *dest, String *src);  /* dest eats src    */
                                            /* following string_swallow     */
                                            /* src is invalid               */
char const *string_short (char const *s);
char const *string_str(String const *sp);
char       *string_strip(char **str);       /* returns *str as stripped str */

#endif
