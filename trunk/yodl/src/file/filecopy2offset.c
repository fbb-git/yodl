#include "file.ih"

void file_copy2offset(FILE *dest, FILE *src, long src_end)
{
    register char *buffer = new_memory(BLOCK_FILE, sizeof(char));
    long tocopy = src_end - ftell(src);
 
    if (tocopy <= 0)                            /* program may have eaten   */
    {                                           /* some bytes, yet          */
        int nread;
        if (src_end != EOF)                     /* not copy to EOF ?        */
            return;                             /* then done                */

        while (true)
        {
            nread = fread(buffer, 1, BLOCK_FILE, src);
            if (nread <= 0)
                return;
            fwrite(buffer, (size_t)nread, 1, dest);
        }
    }

    while                                       /* All until last BLOCK     */
    (
        tocopy > BLOCK_FILE                     /* more than 1 block waits  */
        &&                                      /* AND */
        fread(buffer, BLOCK_FILE, 1, src) == 1  /* we read 1 block */
        &&                                      /* AND */
        fwrite(buffer, BLOCK_FILE, 1, dest) == 1/* we wrote 1 block */
    )
        tocopy -= BLOCK_FILE;

    if                                          /* copy the last block      */
    (
        tocopy <= BLOCK_FILE                    /* at most 1 block waits    */
        &&                                      /* AND */
                                                /* we read the req'd chars  */
        fread(buffer, (size_t)tocopy, 1, src) == 1     
        &&                                      /* AND */
                                                /* we wrote the req'd chars */
        fwrite(buffer, (size_t)tocopy, 1, dest) == 1   
    )
    {
        free(buffer);
        return;
    }

    message_show(MSG_ALERT);
    message("file_copy2offset() r/w error");
}
