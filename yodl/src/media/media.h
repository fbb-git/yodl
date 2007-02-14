#ifndef _INCLUDED_MEDIA_H_
#define _INCLUDED_MEDIA_H_

#include <stdio.h>
#include "../queue/queue.h"

/*
    the Media struct is used only by the lexical scanner (Lexer). Pointers to
    Media structs are passed via the Stack
*/

typedef struct Media
{
    FILE       *d_file;         /* current input file if reading files  */
    size_t    d_lineno;       /* linenumber at push-point             */
    long        d_offset;       /* offset at push-point                 */
    char       *d_filename;     /* name of the file being processed     */
    Queue       d_queue;        /* queue of chars to process            */
    bool        d_isfile;       /* true if file media                   */
    bool        d_fgetc;        /* true if retreived char from file     */
}
Media;

#endif
