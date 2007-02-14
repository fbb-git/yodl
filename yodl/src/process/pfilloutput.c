#include "process.ih"

void p_fill_output(register Process *pp, int fd)
{
    size_t size;
    register char *buffer = new_memory(MAX_LINE_LENGTH + 1, sizeof(char));

    while ((size = read(fd, buffer, MAX_LINE_LENGTH)) != 0)
    {
        buffer[size] = 0;
        string_addstr(pp->d_output, buffer);
    }
    close(fd);
    free(buffer);
}
