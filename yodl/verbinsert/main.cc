#include "main.ih"

int main(int argc, char **argv)
try
{
    Line line;                      // analyzes the line-type
    Process process{ line };        // processes the input stream

    options(process, line, argc, argv); 

    process.run();
}
catch (std::string const &msg)
{
    cerr << msg << '\n';
    return 1;                       // since yodlverbinclude is usually called
}                                   // as a childprocess, 1 is returned if 
catch (int x)                       // something's wrong and also when usage
{                                   // is displayed
    return x;
}
catch (...)
{
    cerr << "unexpected exception\n";
    return 1;
}




