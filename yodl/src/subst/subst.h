#ifndef INCLUDED_SUBST_H_
#define INCLUDED_SUBST_H_


#include "../root/root.h"
#include "../message/message.h"
#include "../string/string.h"

typedef enum
{
    SUBST_TRANSITION,
    SUBST_GETCHAR,              /* get the next char from the Q */
    SUBST_REPLACED,
}
SubstAction;

struct State;

typedef struct Subst
{
    String        d_buffer;
    struct State *d_start_state_ptr;
    struct State *d_current_state_ptr;
    SubstAction (*d_action) (register struct Subst *sp, int ch);
                 /* in subst_action: either s_noSubst or s_subst */
    size_t        d_nReplacements;
    size_t        d_maxReplacements;
}
Subst;

void        subst_construct(Subst *sp);

SubstAction subst_process(Subst *sp, int ch);
char       *subst_get(Subst *sp);
void        subst_insert(Subst *sp, char const *fname,
                                    char const *key, char const *value);
void        subst_allow(Subst *sp, bool yesNo);

/*
    SUBST definitions result in a tree structure where each node is a State
    (see subst.ih) containing a set of chars which indicate a transition to
    a next match-state, a replacement (if available at this state), its parent
    state and a pointer to pointers to States, where pointer i points to the
    state to transit to if charset[i] was encountered.

    SUBST matching proceeds as follows:

    * all externally produced characters are pushed_back on a queue

    * the characters in the queue are processed (see below)

    * once the queue is empty and there are no more externally produced chars
      processing stops.

    Processing the queue:

    * if a character is found in the current state's string (subst_transition)
        * then it is stored in the Subst's buffer
        * and a transition to the next state is performed.
    * otherwise (character isn't found), 
        * if the current match-length == 0, then the char is returned
          for further processing.
        * otherwise (match-length != 0),
            * the longest match is found (visiting the current tree backwards
              until there is a replacement, using the parent links to find a
              previous match if the current state isn't associated with a
              match (happens if SUBST keys ab and abcd were defined, and input
              contains abc)
            * the buffer's
              tail (beyond the matched key) is pushed to the queue's front,
              then the replacement is pushed to the queue's front, and  the
              last-read character (ending the match) is pushed-back, unless
              it's EOF.
*/
          


#endif
