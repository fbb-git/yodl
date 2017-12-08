#ifndef INCLUDED_OUT_
#define INCLUDED_OUT_

#include <string>

class Out
{
    std::string d_indent;                   // std. indentation
    std::string d_vindent;                  // verb( and closing ) indentation
    char const *d_verbEndl = "\n";          // \n immediately after verb
    size_t d_number = 0;                    // line numbers
    size_t d_nLines = 0;                    // # lines written

                                        // pointer to the inserter function
                                        // firstInsert first writes verb(
    void (Out::*d_insert)(std::string const &line)  = &Out::firstInsert;
    void (Out::*d_line)(std::string const &line)    = &Out::plainLine;

    public:
        Out();
        ~Out();                         // writes ) if lines were written

        void noVerbEndl();              // no \n after verb
        void numberLines();             // show line numbers

        void indent(size_t count, int ch);  // indentation specification
        void vindent(size_t count, int ch); // verb's indentation 

        void insert(std::string const &line);   // insert this line
        void emptyLines(size_t nLines);         // insert nLines empty lines
                                                // (if some lines were already
                                                // inserted)

        size_t nLines() const;

    private:
        void firstInsert(std::string const &line);

        void indent(std::string &target, size_t count, int ch);

        void numberedLine(std::string const &line);
        void plainLine(std::string const &line);
};

inline size_t Out::nLines() const
{
    return d_nLines;
}

inline void Out::indent(size_t count, int ch)
{
    indent(d_indent, count, ch);
}

inline void Out::vindent(size_t count, int ch)
{
    indent(d_vindent, count, ch);
}

inline void Out::noVerbEndl()
{
    d_verbEndl = "";
}

inline void Out::numberLines()
{
    d_line = &Out::numberedLine;
}

#endif
