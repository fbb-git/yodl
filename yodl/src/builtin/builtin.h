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
void        builtin_call(Builtin *builtin);
char const *builtin_name(Builtin const *builtin);
void      (*builtin_setAction(Builtin *builtin, void (*)(void)))(void);

#endif
