#ifndef INCLUDED_SUBST_H_
#define INCLUDED_SUBST_H_

#include <stdio.h>

#include "../root/root.h"
#include "../message/message.h"
#include "../string/string.h"
#include "../strvector/strvector.h"

typedef enum
{
    SUBST_CONTINUE,
    SUBST_GETCHAR,
    SUBST_SUBSTITUTION
}
SubstAction;

struct State;

typedef struct
{
    String        d_buffer;
    bool          d_allowSubst;
    struct State *d_start_state_ptr;
    struct State *d_current_state_ptr;
    StrVector     d_strVector;
}
Subst;


void        subst_construct(Subst *sp);
void        subst_destruct(Subst *sp);

SubstAction subst_action(Subst *sp, int ch);
char       *subst_get(Subst *sp);
void        subst_insert(Subst *sp, char const *fname,
                                    char const *key, char const *value);
void        subst_allow(Subst *sp, bool yesNo);

static inline StrVector const *subst_strVector(Subst *sp)
{
    return &sp->d_strVector;
}

#endif






