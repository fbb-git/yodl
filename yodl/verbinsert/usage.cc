//                     usage.cc

#include "main.ih"

namespace {
    char const *info = 
R"(
Where:
 [options] - optional arguments (short options between parentheses):
   -a      process all lines, //marker may not be specified
   -A      same as -a, all marker lines are skipped
   -n      write line numbers
   -N      no newline after verb(
   -s<nr>  indent lines with <nr> space characters
   -t<nr>  indent lines with <nr> tab characters (before spaces)
   -S<nr>  indent verb( and final ) with <nr> space characters
   -T<nr>  indent verb( and final ) with <nr> tab characters (before spaces)

   //marker target marker (not with -a, -A options)
   file     file to be process

Output is written to the std output stream. 

Returns 1 at errors, including showing this usage information. Error output is
written to the std error stream.
)";

}   // namespace

void usage(std::string const &progname)
{
    cerr << "\n" <<
    progname << " by " << author << "\n" <<
    progname << " V" << version << " " << years << "\n"
    "\n"
    "Usage: " << progname << " [options] [//marker] file" << info << '\n';

    throw 1;
}






