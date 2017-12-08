#ifndef INCLUDED_PROCESS_
#define INCLUDED_PROCESS_

#include <string>

#include "../linetype/linetype.h"
#include "../out/out.h"

class Line;

class Process: private LineType
{
    Line &d_line;
    Out d_out;

    void (Process::*d_run)() = 0;

    public:
        Process(Line &line);

                                            // configure Process:
        void all();                         //  -A
        void indent(size_t count, int ch);  // line indentation
        void noVerbEndl();                  // no \n after verb
        void numberLines();                 // lines are numbered
        void setTarget(char const *target); // specify the target marker
        void vindent(size_t count, int ch); // verb-indentation
        
        void run();                         // process the input file

    private:
        void processAll();                  // either process all lines
        void processTarget();               // or process lines in target
                                            // sections 
};

        
inline void Process::all()
{
    d_run = &Process::processAll;
}

inline void Process::noVerbEndl()
{
    d_out.noVerbEndl();
}

inline void Process::indent(size_t count, int ch)
{
    d_out.indent(count, ch);
}

inline void Process::vindent(size_t count, int ch)
{
    d_out.vindent(count, ch);
}

inline void Process::numberLines()
{
    d_out.numberLines();
}

#endif
