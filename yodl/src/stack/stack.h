#ifndef _INCLUDED_STACK_H_
#define _INCLUDED_STACK_H_

#include "../root/root.h"

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

typedef struct
{
    unsigned    d_size;
    unsigned    d_n;
    void        **d_value;
    void (*d_destructor)(void *);
}
Stack;

void    stack_assign(Stack *sp, void *value);  /* if empty, value is pushed */
                                        /* if used, topmost is destroyed    */
                                        /* and `value' is stored instead    */

void    stack_construct(Stack *sp, void (*destructor)(void *));
bool    stack_contains(Stack *sp, void const *value);       /* true: yes    */
void    stack_destroy(void *sp);
void    stack_pop(Stack *sp);           /* removes top elemenet from stack  */

                                        /* always SUCCESS, but sp must be   */
                                        /* a valid pointer                  */
Result  stack_push(Stack *sp, void *value);
void   *stack_tos(Stack const *sp);     /* ptr->topmost element or PFAILED */
unsigned stack_size(Stack const *sp);

#endif
