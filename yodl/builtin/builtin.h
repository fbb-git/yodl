#ifndef INCLUDED_BUILTIN_H_
#define INCLUDED_BUILTIN_H_

#include "../hashmap/hashmap.h"

typedef struct
{
    char const *d_name;
    void (*d_action)(void);
}
Builtin;


Builtin    *builtin_copy(Builtin const *builtin);
void        builtin_insert(HashMap *symtab, Builtin *builtin);
char const *builtin_name(Builtin const *builtin);
void      (*builtin_setAction(Builtin *builtin, void (*)(void)))(void);

static inline void builtin_call(Builtin *builtin)
{
    (*builtin->d_action)();
}

#endif
