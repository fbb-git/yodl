#include "process.ih"

void Process::processAll()
{
    size_t nEmpty = 0;

    while (true)
    {
        d_line.next();

        switch (d_line.type())
        {
            case EMPTY:
                ++nEmpty;
            break;
            
            case TARGET:
            case ENDTARGET:
            case TEXT:
                if (nEmpty)
                {
                    if (d_out.nLines())
                        d_out.emptyLines(nEmpty);
                    nEmpty = 0;
                }
                d_out.insert(d_line.line());
            [[fallthrough]]

            default:
            break;

            case ENDFILE:
            return;
        }
    }
}
