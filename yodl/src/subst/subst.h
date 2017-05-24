#ifndef INCLUDED_SUBST_H_
#define INCLUDED_SUBST_H_

#include <stdio.h>

#include "../root/root.h"
#include "../message/message.h"
#include "../string/string.h"

typedef enum
{
    SUBST_CONTINUE,
    SUBST_GETCHAR,
    SUBST_SUBSTITUTION
}
SubstAction;

typedef struct Subst
{
    String      d_buffer;
    void       *d_start_state_ptr;
    void       *d_current_state_ptr;
    SubstAction (*d_action) (register struct Subst *sp, int ch);
                 /* in subst_action: either s_noSubst or s_subst */
}
Subst;


SubstAction subst_action(Subst *sp, int ch);
void        subst_construct(Subst *sp);
char       *subst_get(Subst *sp);
void        subst_insert(Subst *sp, char const *fname,
                                    char const *key, char const *value);
void        subst_allow(Subst *sp, bool yesNo);

#endif
