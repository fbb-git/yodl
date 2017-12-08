#include "process.ih"

void Process::processTarget()
{
    while (true)
    {
        while (not (d_line.next() & (TARGET | ENDFILE)))
            ;

        if (d_line.type() == ENDFILE)
            return;

        while (not (d_line.next() & (ENDTARGET | ENDFILE)))
            d_out.insert(d_line.line());

        if (d_line.type() == ENDFILE)
            throw string { "end marker for `" } + d_line.target() + 
                    "' not found";
    }
}
