#ifndef _INCLUDED_LEXER_H_
#define _INCLUDED_LEXER_H_

#include "../stack/stack.h"
#include "../string/string.h"
#include "../subst/subst.h"

typedef enum                /* Modify ldata.c when this enum is altered     */
{                           /* ========================================     */
    TOKEN_UNKNOWN,

    TOKEN_SYMBOL,
    TOKEN_TEXT,
    TOKEN_PLAINCHAR,        /* formerly: anychar */
    TOKEN_OPENPAR,
    TOKEN_CLOSEPAR,
    TOKEN_PLUS,             /* it's semantics what we do with a +, not      */
                            /* something for the lexer to worry about       */

    TOKEN_SPACE,            /* Blanks should be at the end                  */
    TOKEN_NEWLINE,

    TOKEN_EOR,              /* end of record: ends pushed strings           */
    TOKEN_EOF,              /* at the end of nested evaluations/eof         */

    SIZEOF_TOKEN            /* Not a token, but counts the number of tokens */
}
LEXER_TOKEN;

/*
    When the lexer should read a file, a filename, lineno and offset are made
available. Alternatively, when processing a file, a macro or other expandable
item may be encountered. In that situation, the lexer may be requested to
continue reading from memory (a C-string).
*/

typedef struct Lexer
{
    Subst      *d_subst_ptr;

    Stack       d_empty_st;     /* stack of media-stack indices at which    */
                                /* the Lexer will consider the media        */
                                /* stack empty.                             */

    bool        d_keep_ws;      /* if true, newlines and blanks at the      */
                                /* begin of lines are kept (not related to  */
                                /* \EOLN handling                           */
    unsigned    d_empty_size;   /* size of the media stack where the media  */
                                /* stack is considered empty. At this point */
                                /* popping is not allowed anymore, and EOF  */
                                /* will consequently be returned.           */
                                /* lexer_end_eval() is the only available   */
                                /* facility to reset d_empty_size to a      */
                                /* lower value                              */

    Stack       d_media_st;     /* stack of media processed by the lexer    */

    void       *d_media_ptr;    /* points to top-element of media if def'd  */
                                /* If the media stack is empty, d_media is  */
                                /* NULL                                     */

    LEXER_TOKEN d_token;
    int         d_lastchar;

    String      d_text;         /* matched text (reset at each token)       */

    unsigned    d_filedepth;    /* number of nested files                   */
    unsigned    d_maxdepth;     /* maximum number of nested files           */
    unsigned    d_nreplacements;/* number of macro/subst replacements since */
                                /* last fgetc() call                        */
    unsigned    d_maxreplacements;  /* maximum allowed number of            */
                                    /* macro/subst replacements             */
}
Lexer;
                                            /* begin nested evaluation      */
                                            /* stack                        */
void        lexer_begin_nested(Lexer *lp, char const *txt);
void        lexer_construct(Lexer *lp, Subst *sp);
void        lexer_end_nested(Lexer *lp);    /* restore evaluation stack     */
                                            /* after nesting                */
char const *lexer_filename(Lexer *lp);
LEXER_TOKEN lexer_lex(Lexer *lp);
unsigned    lexer_lineno(Lexer *lp);
void        lexer_push_file(Lexer *lp, char const *filename);
void        lexer_push_str(Lexer *lp, char const *str);
void        lexer_set_keep_ws(Lexer *lp, bool trueIsYes);
char const *lexer_text(Lexer *lp);             /* matching _lex() text      */
LEXER_TOKEN lexer_token(Lexer *lp);
char const *lexer_tokenName(LEXER_TOKEN token);
void        lexer_unget_matched(Lexer *lp);

#endif
