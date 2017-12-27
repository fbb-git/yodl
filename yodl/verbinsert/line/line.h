#ifndef INCLUDED_LINE_
#define INCLUDED_LINE_

#include <string>
#include <fstream>
#include <regex>

#include "../linetype/linetype.h"

class Line: public LineType
{
    static std::regex s_markerBegin;
    static std::regex s_markerEnd;

    std::ifstream *d_in = 0;            // allocated
    std::istream *d_input;              // not allocated

    Type d_type = UNKNOWN;
    std::string d_line;

    std::string d_target;
    bool d_begin = true;                // endtarget if not d_begin
    bool d_ignore = false;              // ignore some lines

    bool (Line::*d_matchMarker)() = &Line::markerPattern;

    public:
        Line();
        ~Line();

        void open(std::string const &name);

        Type next();                        // get the next line
        void setTarget(char const *target); // set the target line
        void ignore();                      // set d_ignore (e.g., with -A)

        Type type() const;                  // accessors
        std::string const &line() const;
        std::string const &target() const;

        void all();

    private:
        bool isEmpty() const;
        bool markerPattern();
        bool noMarker();
};

inline void Line::all()
{
    d_matchMarker = &Line::noMarker;
}

inline void Line::ignore() 
{
    d_ignore = true;
}

inline Line::Type Line::type() const
{
    return d_type;
}

inline void Line::setTarget(char const *target)
{
    d_target = target;
}

inline std::string const &Line::line() const
{
    return d_line;
}
        
inline std::string const &Line::target() const
{
    return d_target;
}
        
#endif





