#ifndef INCLUDED_POSTQUEUE_H_
#define INCLUDED_POSTQUEUE_H_

#if 0

    Postprocessing is realized by a template-method design pattern-like
construction in C.

    The algorithm proceeds as follows:

    Each element of the index file is read, and its keyword (the word
following the offfset) is determined. Then the 'construct' function associated
with that keyword is called. We agree with the construct functions that they
return a pointer to a hashitem, which is then processed by storing it either
into the the symbol table or into the work-queue. The construct functions
can use all  postqueue_...() new_...(), message_()... string_..()
args_...(), and file_...()  functions.

    Then, when all commands are available, the queued commands are
processed. For this, the appropriate 'handle' functions are called. Use 0 for
situations where no handling is required.

To conserve memory, having handled a Q-item, its HashItem is erased. The
caller can prevent the destruction of information stored at the HashItems
d_value pointer by setting the HashItems destructor to root_nop. This way the
information remains available for other parts of the program, if made known to
these parts using, e.g., a well-known variable name.


    The handling struct is hashed by keywords found in the Task struct, having
the following elements:

typedef struct
{
    char const *d_key;
    HashItem *(*d_constructor)(long offset, char const *key,
                               char *rest);

    void      (*d_handler)(HashItem *item);
}
Task;

In order to construct a postprocessor, use the postprocessor and postqueue
c.s. directories, and link them to an appropriate handler directory.

The main function should be set up as follows:

    int main (int argc, char **argv)
    {
        postqueue_initialize(argc, argv, "-getopt-options string",
                             long_options_pointer);

        if (!args_ok() || args_nArgs() != 2)    /* check arguments */
            usage();

        postQueue_construct(task_pointer);
        postQueue_process();
    }

The usage() function must be defined for the particular postprocessor
and end in exit(1)

the long_options_pointer must end in an element of all zeroes, and otherwise
consist of LongOption values. See args.h: each element has 3 fields:

    char const *: name of the long option (without --)
    type: one of
            required_argument   - an argument is required
            no_argument         - the option has no argument
            optional_argument   - the argument is optional
    char:   the (character) value associated with this option E.g., 'v' with
            version, of a unique other value if no corresponding single char.
            option is available.


The task-struct is defined in this header file. The array passed to the
constructor must have a final zero-element The constructor returns a hashitem
The hashitem is appended to the task-queue. The type of the hashitem is not
used by the postprocessor, and may be used at will by the constructor or
handler functions.

After processing the index file, the task queue is processed, where each
element of the queue is processed by its handler.

Since this class and its functions are always used by the postprocessors, it
includes for convenience the basic header files:

    stdio.h,

    root, new, message, string, hashmap, hashitem, file, args

#endif


#include <stdio.h>

#include "../root/root.h"
#include "../args/args.h"
#include "../new/new.h"
#include "../message/message.h"
#include "../file/file.h"
#include "../hashmap/hashmap.h"
#include "../hashitem/hashitem.h"
#include "../string/string.h"

typedef struct
{
    char const *d_key;
    HashItem *(*d_constructor)(char const *key, char *rest);
    void      (*d_handler)(long offset, HashItem *item);
}
Task;

extern int postqueue_data;

void  postqueue_construct(Task *taskptr);
void  postqueue_process(void);  /* erases and destroys the HashItem structs */
                                /* after calling their handlers             */

/* 
    Internal use only. Not used outside of this directory, needed here
    to allow proper compilation of the static inline functions below
*/

typedef struct
{
    long      d_offset;
    HashItem *d_item;
    void    (*d_handler)(long, HashItem *);
}
QueueItem;

typedef struct
{
    char      **d_argv;
    QueueItem **d_queue;
    unsigned    d_size;         /* available number of pointer locations    */
    unsigned    d_length;       /*  actually used # of items                */
    FILE       *d_istream;
}
PostQueue;

extern PostQueue postQueue;

/*  public interface continues from here */


static inline FILE *postqueue_istream(void)
{
    return postQueue.d_istream;
}

#endif
