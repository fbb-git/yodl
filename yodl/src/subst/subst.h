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

typedef struct
{
    String      d_buffer;
    bool        d_allowSubst;
    void       *d_start_state_ptr;
    void       *d_current_state_ptr;
}
Subst;


void        subst_construct(Subst *sp);

SubstAction subst_action(Subst *sp, int ch);
char       *subst_get(Subst *sp);
void        subst_insert(Subst *sp, char const *fname,
                                    char const *key, char const *value);
void        subst_allow(Subst *sp, bool yesNo);

#endif
