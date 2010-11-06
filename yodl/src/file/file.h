#ifndef INCLUDED_FILE_H_
#define INCLUDED_FILE_H_

#include <stdio.h>
#include "../hashmap/hashmap.h"

void    file_append(FILE *dest, char const *path);  /* dest must be open    */
char   *file_basename(char const *path);
void    file_copy2offset(FILE *dest, FILE *src, long src_end);
char   *file_dirname(char const *path);

                                    /* extension: extension (without .)     */
char   *file_extension(char const *path);

            /* Full pathname of `filename' is returned as allocated string  */
            /* or NULL if no file was found. The path defined by the        */
            /* XXincludePath symbol and the default extension (.yo) are     */
            /* used when searching for `filename'                           */
            /* When returning a pathname, the file can be read.             */
            /* $HOME in the spec. is replaced by the caller's home dir.     */
            /* (if available from the $HOME or $home environment vars)      */
char *file_fullpath(HashMap *symtab, char const *filename);

                                    /* rmExtension: new string without ext. */
char   *file_rmExtension(char const *path);

            /* NULL: couldn't open `name' in the indicated mode ("r", "w")  */
            /* otherwise a FILE* for the requested file.                    */
FILE   *file_open(char const *name, char const *mode);

/* 
    Internal File use only. Not used outside of this directory, needed here
    to allow proper compilation of the static inline functions below
*/

#include "../symbol/symbol.h"


/*  public interface continues from here */

            /* NULL: no XXincludePath defined                               */
static inline char const *file_includePath(HashMap *symtab)
{
    return symbol_value(hashmap_find(symtab, "XXincludePath", SYMBOL));
}

#endif
