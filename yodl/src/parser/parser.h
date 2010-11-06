#ifndef INCLUDED_PARSER_H_
#define INCLUDED_PARSER_H_

#include <stdio.h>
#include <stdlib.h>

#include "../stack/stack.h"
#include "../hashmap/hashmap.h"
#include "../lexer/lexer.h"
#include "../ostream/ostream.h"
#include "../chartab/chartab.h"

typedef enum
{
    COLLECT_SET,                /* retrieve the parameter list as it is */
                                /* encountered on the input             */

    DEFAULT_SET,                /* process macros, builtins etc.        */
                                /* By default phandle_insert() is       */
                                /* called                               */

    NOTRANS_SET,                /* insert the parameter list using the  */
                                /* currently active insertion function  */
                                /* otherwise identical to NOEXPAND_SET  */
                                /* The character translation table is   */
                                /* not used                             */

    IGNORE_SET,                 /* completely skip the parameter list   */

    NOEXPAND_SET,               /* do not expand the parameter list     */
                                /* but return the parameterlist         */
                                /* CHAR() is interpreted                */

    SKIPWS_SET,                 /* consume all ws characters            */
                                /* lexer_lex() returns the next non-ws  */
                                /* character                            */

    SIZEOF_HANDLER_SET_ELEMENTS
}
HANDLER_SET_ELEMENTS;
    /* see also phandler.c and pparse.c */

typedef struct Parser
{
    bool        d_show_nomacros;        /* show non-macro calls             */
    size_t      d_max_macro_nesting;    /* max nesting level when calling   */
                                        /* (user defined) macros            */
    bool        d_keep_ws;              /* true: lexer keeps initial ws on  */
                                        /* lines                            */
    int         d_ws_level;             /* ws skiplevel                     */
    Stack       d_ws_level_st;          /* stacked wslevels when pushing    */
    size_t      d_parcount;             /* increments at each new paragraph */
                                        /* activation. Accesible as         */
                                        /* counter XXparcount               */
    size_t      d_parlist_lineno;       /* begin line and filename of       */
    char       *d_parlist_filename;     /* a parameter list                 */
                                        /* (used for handling premature EOF */
                                        /* when scanning parameter lists)   */
    size_t      d_paren;                /* counts parentheses of current    */
                                        /* parameter list                   */
    Stack       d_paren_st;             /* counts parentheses               */
                                        /* in open-/closeparen() functions  */
    Subst       d_subst;
    Lexer       d_lexer;
    Stack       d_atexit_st;            /* stores char *'s                  */
    Stack       d_string_st;            /* stores String *'s which are      */
                                        /* returned, and should not be      */
                                        /* destroyed by the stack           */
    String      *d_string_ptr;          /* output media for insert_string() */
    Ostream     *d_outs_ptr;            /* output media for insert_ostream()*/
    char        *d_indexName;           /* name of the index file (or 0)    */
    FILE        *d_indexFile;           /* file containing the index        */

                /* d_insert determines the target for the produced output   */
                /* this can be a String or an Ostream. It is set by         */
                /* various functions to obtain nested text. Used by         */
                /* the interrnal p_filter and p_dont_filter functions to    */
                /* find the destination of the produced characters          */
    void (*d_insert)(struct Parser *, char const *);
    Stack d_insert_st;                  /* stacked inserters                */


                /* d_handle is a pointer to an array of pointers to         */
                /* functions, having as element for each defined lexical    */
                /* scanner token, defining how to process that particular   */
                /* token in a given situation.                              */
                /* The functions are all called p_handle...., and return    */
                /* bool if processing should continue                       */
    bool (**d_handler)(struct Parser *);    /* active set of handlers       */
    Stack d_handler_st;                     /* stacked handler ptrs         */

    HashMap     *d_symtab_ptr;
}
Parser;

extern int parser_data;

void        parser_apply_chartab(register Parser *pp);
void        parser_atexit(Parser *pp, char *text);
void        parser_construct(Parser *pp, HashMap *symtab, Ostream *outs);
void        parser_discard(Parser *pp, SymbolType type,
                           char const *fun, char const *msg);
void        parser_empty_parlist(Parser *pp);
char       *parser_eval(register Parser *pp, register char *arg);
void        parser_if(Parser *pp, SymbolType type, char const *fun);
void        parser_if_cond(Parser *pp,
                            bool (*comparator)(Parser *pp, char **parlist),
                            char const *fun, size_t nparlists);
bool        parser_if_empty(Parser *pp, char **parlist);
bool        parser_if_equal(Parser *pp, char **parlist);
bool        parser_if_greater(Parser *pp, char **parlist);
bool        parser_if_smaller(Parser *pp, char **parlist);
bool        parser_if_strsub(Parser *pp, char **parlist);
bool        parser_if_zero(Parser *pp, char **parlist);
void        parser_includefile(Parser *pp, char const *filename);
char       *parser_name_parlist(Parser *pp, bool skipws);
char       *parser_nochartab_eval(register Parser *pp, register char *arg);
void        parser_noexpand_include(Parser *pp,
                                    char const *filename, bool searchPath);
Result      parser_number_parlist(Parser *pp, int *value, bool skipws);
void        parser_push_fun(char const *name);
void        parser_push_ws_level(Parser *pp, int value);
void        parser_pop(Parser *pp, SymbolType type, char const *fun,
                                                            char const *msg);

            /* NULL with INSERT_SET, IGNORE_SET and NOEXPAND_SET            */
            /* never NULL with COLLECT_SET and DEFAULT_SET                  */
            /* never returns outer ()                                       */
            /* consumes the parlist including the outer ()                  */
void        parser_pop_ws_level(Parser *pp);
char       *parser_parlist(Parser *pp, HANDLER_SET_ELEMENTS newSet);

void        parser_process(Parser *pp);
void        parser_skipws(Parser *pp);
char const *parser_strvalue(register Parser *pp, char const *txt);

void      (*parser_suppress_chartab(Parser *pp))
                                            (struct Parser *, char const *);

Result      parser_value(Parser *pp, int *value, char const *text);

/* 
    Internal Parser use only. Not used outside of this directory functions, needed here
    to allow proper compilation of the static inline functions below
*/

extern Stack ps_fun_st;              /* stores the names of functions    */

void    p_set_ws_level(Parser *pp, int value);


/*  public interface continues from here */


static inline size_t parser_ws_level(register Parser *pp)
{
    return pp->d_ws_level;
}

static inline void parser_pop_fun()
{
    stack_pop(&ps_fun_st);
}

static inline void parser_inc_ws_level(register Parser *pp)
{
    p_set_ws_level(pp, ++pp->d_ws_level);
}

static inline char const *parser_fun()
{
    return stack_tos(&ps_fun_st)->u_charCp;
}

static inline void parser_dec_ws_level(register Parser *pp)
{
    p_set_ws_level(pp, --pp->d_ws_level);
}

static inline bool parser_if_strequal(register Parser *pp, 
                                      register char **parlist)
{
    return !strcmp(parser_strvalue(pp, parlist[0]), 
            parser_strvalue(pp, parlist[1]));
}

#endif
