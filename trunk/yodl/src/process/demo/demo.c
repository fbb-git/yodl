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
#include "../../root/root.h"
#include "../../message/message.h"
#include "../process.h"

int main(int argc, char **argv)
{
    String *cmd = string_new(0);
    String *input = NULL;

    if (argc == 1)
    {
        fprintf(stderr,
            "Usage: %s [-s] prog [arg(s)]\n"
            "      -s: use system call, not std-input\n"
            "    prog: program or system call to execute\n"
            "  arg(s): optional arguments to prog\n"
            "Input to prog is read from stdin, unless -s was specified\n"
            "   (don't make this too long, it's stored in a String first)\n"
            "\n",
            argv[0]);

        exit(1);
    }

    bool syscall = !strcmp(argv[1], "-s");
    if (syscall)
    {
        argc--;
        argv++;
    }
    else
    {
        input = string_new(0);
        char buffer[100];

        fprintf(stderr, "Reading input from stdin...\n");

        while (fgets(buffer, 100, stdin))
            string_addstr(input, buffer);

        fprintf(stderr, "Input will be:\n"
                        "`%s'\n", string_str(input));
    }

    while (*++argv)
    {
        string_addstr(cmd, *argv);
        string_addchar(cmd, ' ');
    }


    fprintf(stderr, "Command will be:\n"
                        "`%s'\n", string_str(cmd));

    message_setseverity(MSG_ALL);
    message(MSG_NOTICE, "Creating Process");

    Process process;
    process_construct(&process, "process-demo", cmd,
                                                input);

    if (syscall)
        process_system(&process);
    else
        process_fork(&process);

    String const *out = process_output(&process);

    fprintf(stderr, "Output from process: '\n"
            "%s\n"
            "'\n", string_str(out));

    process_destroy(&process);

    return 0;
}
