#ifndef INCLUDED_STRING_H_
#define INCLUDED_STRING_H_

/*
    String stores ascii-Z strings. Char * args may be NULL.

    string_format() assumes C99 is active (see the snprintf() manpage)
*/

#include "../root/root.h"

#include <stdarg.h>
#include <string.h>

typedef struct
{
    size_t d_size;        /* buffer size of d_str        */
    size_t d_length;      /* length not counting ascii-Z */
    char *d_str;
}
String;

void        string_add(String *dest, String *src);
void        string_addchar(String *sp, int c);      /* actually: c is a char */
void        string_addcharOnce(String *sp, int c);  /* not if already there */
void        string_additerators(String *string, char const *begin,
                                                char const *end);
void        string_addstr(String *sp, char const *str);
void        string_assign(String *sp, char const *str);
void        string_copy(String *dest, String *src);
size_t      string_count(String *sp, char needle);
void        string_destructor(void *sp);            /* frees sp + contents  */
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
char       *string_strip(char **str);       /* returns *str as stripped str */


/* 
    Internal String use only. Not used outside of this directory, needed here
    to allow proper compilation of the static inline functions below
*/

#include <stdlib.h>

extern char const s_stringEmpty[];
void s_init(String *sp, char const *txt);       /* disregards sp's contents */


/*  public interface continues from here */


static inline char const *string_str(register String const *sp)
{
    return sp->d_str;
}

static inline size_t string_length(register String const *sp)
{
    return sp->d_length;
}

static inline void string_erase(String *sp)     /* resets to "" */
{
    string_assign(sp, 0);
}

static inline void string_destroy(register String *sp)
{
    free(sp->d_str);
}

static inline void string_construct(String *s, char const *str)
{
    s_init(s, str ? str : s_stringEmpty);
}

static inline int string_last(String const *sp)
{
    return sp->d_length == 0 ? 0 : sp->d_str[sp->d_length - 1];
}

#endif



