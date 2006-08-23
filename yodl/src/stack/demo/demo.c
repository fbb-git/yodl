/*
    Compile using

    gcc demo.c ../out/library.a \
                ../../string/out/library.a \
                ../../new/out/library.a \
                ../../message/out/library.a \
                ../../root/out/library.a
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../../root/root.h"
#include "../../message/message.h"
#include "../stack.h"

int main(int argc, char **argv)
{
    Stack intStack;                         /* stack of ints                */
    Stack txtStack;                         /* stack of char *'s            */
    int idx;

    stack_construct(&intStack, NULL);       /* no destructor                */
    stack_construct(&txtStack, free);       /* free() is destructor         */
    stack_destroy(&txtStack);               /* destroy an empty stack       */
    stack_construct(&txtStack, free);       /* reconstruct it               */

    for (idx = 0; idx < 20; idx++)          /* Push 10 values on inttack    */
    {
        stack_push(&intStack, (void *)(2 * idx));
        printf("Intstack %d contains %d\n", idx, stack_tos(&intStack));
    }
    stack_assign(&intStack, (void *)100);   /* reassing topmost element     */
    printf("intstack has %u elements\n", stack_size(&intStack));

    for (idx = 0; idx < 5; idx++)           /* Pop 5 values from inttack    */
    {
        printf("After popping %d elements, top contains %d\n",
                                        idx, stack_tos(&intStack));
        stack_pop(&intStack);
    }

    stack_destroy(&intStack);               /* destroy the rest             */


    for (idx = 0; idx < argc; idx++)        /* Push argv's on txtstack      */
    {
        stack_push(&txtStack, new_str(argv[idx]));
        printf("Txtstack %d contains %s\n", idx, stack_tos(&txtStack));
    }
                                            /* reassing topmost element     */
    stack_assign(&txtStack, new_str("Hello world"));
    printf("txtstack has %u elements\n", stack_size(&txtStack));

    for (idx = 0; idx < argc - 1; idx++)    /* Pop all elements but one     */
    {
        printf("After popping %d elements, top contains %s\n",
                                        idx, stack_tos(&txtStack));
        stack_pop(&txtStack);
    }

    printf("txtstack has %u elements\n", stack_size(&txtStack));
    stack_destroy(&txtStack);               /* destroy the stack            */

}
