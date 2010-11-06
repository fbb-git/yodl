#ifndef INCLUDED_STACK_H_
#define INCLUDED_STACK_H_

#include "../root/root.h"
#include "../string/string.h"
#include "../media/media.h"

/*
    The stack's destructor destroys the contents of the elements of the
stack. So, at destruction time d_destructor(d_value[idx]) is called.

    The stack_constructor's argument may be NULL, in which case no destruction
takes place.

    If the element itself is a pointer to a plainly allocated block of memory,
then free()'s address may be specified to free the element.

    If the element itself is a dynamically allocated  struct, itself
containing allocated memory, then the destructor should:
        1. free the memory allocated by the struct
        2. free the struct itself.

    Use the following convention:
        X_destroy(X *xp) destroys any memory allocated by the X struct,
        X_destructor(X *xp) calls X_destroy(xp), and then free(xp).

    Elements the size of a pointer can be stored safely in the stack, when
NULL is specified as the destructor (e.g., ints). However, in that case
stack_tos()'s return value PFAILED cannot be discerned from the value FAILED,
which may be at the stacktop. However, if stack_size() returns a value != 0,
stack_tos()'s return value is always ok.

*/

struct Parser;      /* required for the StackValue union definition */

typedef union       /* Note: all fields start with u_, which doesn't mean   */
{                   /* `unsigned'                                           */

    char           *u_charp;
    char const     *u_charCp;
    char          **u_charpp;
    char const    **u_charCpp;
    int             u_int;
    size_t          u_size_t;
    void           *u_voidp;
    void const     *u_voidCp;

    Media          *u_Media;
    String         *u_Stringp;

                    /* Parser function pointers */

    bool (**u_Pfun1p)(struct Parser *);
    void (*u_Pfun2p)(struct Parser *, char const *);
}
StackValue;

typedef struct
{
    size_t    d_size;
    size_t    d_n;
    StackValue *d_value;
    void (*d_destructor)(void *);
}
Stack;

void    stack_assign(Stack *sp, StackValue value);  
                                        /* if empty, value is pushed        */
                                        /* if used, topmost is destroyed    */
                                        /* and `value' is stored instead    */
void    stack_construct(Stack *sp, void (*destructor)(void *));
                                        /* only used by chartab_find()      */
bool    stack_contains(Stack *sp, char const **ctab);       /* true: yes    */
void    stack_destroy(void *sp);
void    stack_pop(Stack *sp);           /* removes top elemenet from stack  */

                                        /* always SUCCESS, but sp must be   */
                                        /* a valid pointer                  */
Result  stack_push(Stack *sp, StackValue value);

/* 
    Internal Stack use only. Not used outside of this directory, needed here
    to allow proper compilation of the static inline functions below
*/

extern StackValue stFailed;


/*  public interface continues from here */


                                        /* topmost element or {PFAILED}     */
static inline StackValue *stack_tos(Stack const *sp)
{
    return sp->d_n ? sp->d_value + sp->d_n - 1 : &stFailed;
}

static inline size_t stack_size(Stack const *sp)
{
    return sp->d_n;
}

#endif



