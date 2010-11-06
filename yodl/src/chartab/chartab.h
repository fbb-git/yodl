#ifndef INCLUDED_CHARTAB_H_
#define INCLUDED_CHARTAB_H_

#include <sys/types.h>
#include <regex.h>

#include "../root/root.h"
#include "../stack/stack.h"
#include "../hashmap/hashmap.h"
#include "../string/string.h"

/*
    Character tables are defined as arrays of 256 char *s and stored
    by name in the symbol table. In d_chartab_st the addresses of the tables
    are stored, stackwise, while d_active is always set to the stack's top to
    speed up chartable access.
    There is no default character table. If the default is requested, NULL is
    pushed on the stack.
*/

typedef struct
{
    Stack d_chartab_st;     /* pointers to stacked character tables         */
    char **d_active;        /* currently active character table NULL if     */
                            /* the default (1:1) chartab is active          */
    regex_t d_regex;        /* compiled regular expression                  */
    regex_t d_regex_oct;    /* compiled regular expression (octal char)     */
    regex_t d_regex_hex;    /* compiled regular expression (hex char)       */

}
Chartab;

extern int chartab_data;   /* to ensure linkage via chartabconstruct.c     */

String     *chartab_apply(char const *txt); /* returns transformed text     */
                                            /* MUST have active chartab     */

void        chartab_construct(void);
Result      chartab_find(char const **chartab);
Result      chartab_insert(HashMap *symtab, char const *name, char *table);
Result      chartab_pop(void);              /* pop the most recent chartab  */
                                            /* activate the previous one    */

                                            /* push and activate the named  */
                                            /* chartab, or no chartab for   */
                                            /* an empty string              */
Result      chartab_use(HashMap *symtab, char const *name, bool pushIsTrue);

/* 
    Internal Chartab use only. Not used outside of this directory functions, needed here
    to allow proper compilation of the static inline functions below
*/

extern Chartab chartab;                     /* there's only one chartab     */
                                            /* storage                      */

/*  public interface continues from here */

static inline char const **chartab_active() /* returns active chartab or 0  */
{
    return (char const **)chartab.d_active;
}

static inline void chartab_destroy(void *chartable)
{}

static inline bool chartab_isActive()
{
    return chartab.d_active != NULL;
}

#endif
