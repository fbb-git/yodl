#include "process.ih"

void Process::processTarget()
{
    while (true)
    {
                                    // find a target or the end of file
        while (not (d_line.next() & (TARGET | ENDFILE)))
            ;

                                    // done at end of file
        if (d_line.type() == ENDFILE)
            return;

        while (not (d_line.next() & (ENDTARGET | ENDFILE)))
            d_out.insert(d_line.line());

        if (d_line.type() == ENDFILE)
            throw string { "end marker for `" } + d_line.target() + 
                    "' not found";
    }
}


