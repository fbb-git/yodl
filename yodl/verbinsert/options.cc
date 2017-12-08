#include "main.ih"

void options(Process &process, Line &line, int argc, char **argv)
{
    string progName = fs::path{argv[0]}.filename();

    bool all = false;
    try
    {
        while (true)
        {
            switch(int c =  getopt(argc, argv, "aAnNs:S:T:t:v:V:"))
            {
                case 'A':
                    line.ignore();
                [[fallthrough]]

                case 'a':
                    process.all();
                    all = true;
                continue;
    
                case 's':
                    process.indent(stoul(optarg), ' ');
                continue;
    
                case 't':
                    process.indent(stoul(optarg), '\t');
                continue;
    
                case 'S':
                    process.vindent(stoul(optarg), ' ');
                continue;
    
                case 'T':
                    process.vindent(stoul(optarg), '\t');
                continue;
    
                case 'N':
                    process.noVerbEndl();
                continue;
    
                case 'n':
                    process.numberLines();
                continue;
    
                case -1:
                throw true;             // ends option recognition
    
                default:
                    throw string{ "option `"} + static_cast<char>(c) +
                                "' not supported";
            }
        }
    }
    catch (bool)             // catches the -1
    {}
                // remaining arguments (argc - optind) must be 2 if -a was not
                // specified, because then a marker is required, and 1 if -a
                // was not specified.  the last option remains argv[arc - 1]
    if (argc - optind != 2 - all)
        usage(progName);

    if (not all)
        process.setTarget(argv[optind]);

    line.open(argv[argc - 1]);
}







