#ifndef INCLUDED_MEDIA_H_
#define INCLUDED_MEDIA_H_

#include <stdio.h>
#include "../queue/queue.h"

/*
    the Media struct is used only by the lexical scanner (Lexer). Pointers to
    Media structs are passed via the Stack
*/

typedef struct Media
{
    FILE       *d_file;         /* current input file if reading files  */
    size_t      d_lineno;       /* linenumber at push-point             */
    long        d_offset;       /* offset at push-point                 */
    char       *d_filename;     /* name of the file being processed     */
    Queue       d_queue;        /* queue of chars to process            */
    bool        d_isfile;       /* true if file media                   */
    bool        d_fgetc;        /* true if retreived char from file     */
}
Media;

    /*
        All _media_ functions may only be called when the Media * points
        to actual Media
    */
void            media_destructor(void *mp);
int             media_get(Media *mp);         /* gets next char fm media  */
void            media_push_front(Media *mp, char const *str);
void            media_restore_state(Media *mp);
void            media_save_state(Media *mp);  /* info about current media */
                                                /* if it's a file, save its */
                                                /* info and close it        */

static inline bool media_fgetc(Media *mp)     /* true if char returned  */
{
    return mp->d_fgetc;
}

static inline char const *media_filename(register Media *mp)
{
    return mp->d_filename;
}
                                              /* 0 (no media) or linenr   */
static inline size_t media_lineno(register Media *mp)
{
    return mp->d_lineno;
}
                                                /* true: media refers to a  */
                                                /* file, false: to memory   */
                                                /* or no media              */
static inline bool media_isFile(register Media *mp)
{
    return mp->d_isfile;
}
                                                /* unget_memory() assumes   */
                                                /* enough room in d_memory  */
static inline void media_unget_memory(register Media *mp, int ch)
{
    queue_unget(&mp->d_queue, ch);
}

#endif
