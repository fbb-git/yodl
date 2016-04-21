#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <unistd.h>
#include <regex>

using namespace std;

int main(int argc, char **argv)
{
    string progName(argv[0]);

    switch (size_t pos = progName.rfind('/'))
    {
        case string::npos:
            progName.erase(0, pos);
        break;
    }

    size_t nrPrefix = 0;

    string indent;
    string vindent;

    char const *verbendl = "\n";
    bool all = false;
    bool labelFound = false;    
    bool nesting = false;

    while (true)
    {
        int c;
        switch(c =  getopt(argc, argv, "aAnNs:S:T:t:v:V:"))
        {
            case 'A':
                nesting = true;
            // FALLING THRU
            // 
            case 'a':
                all = true;
                labelFound = true;
            continue;

            case 's':
                indent.append(stoul(optarg), ' ');
            continue;

            case 't':
                indent.insert(0, stoul(optarg), '\t');
            continue;

            case 'S':
                vindent.append(stoul(optarg), ' ');
            continue;

            case 'T':
                vindent.insert(0, stoul(optarg), '\t');
            continue;

            case 'N':
                verbendl = "";
            continue;

            case 'n':
                nrPrefix = 1;
            continue;

            case -1:
            break;

            default:
            return 1;
        }
        break;                          /* only at case -1 */
    }

    if (argc - optind < 2 - all)
    {
        cerr << "usage: " << progName << 
            "[-a] [-N] [-n] [-s<nr>] [-t<nr>] [-S<nr>] [-T<nr>] marker file\n"
            "See also: `man yodlverbinsert'\n";

        return 0;
    }

    argv += optind - all;

    string label;
    string endlabel;

    if (not all)
    {
        label = argv[0];
        nesting = label[2] == '+';
        endlabel =                      // define the end-label
                nesting ? 
                    label
                :
                    label[1] == '/' ? "//=" : "/**/";
    }

    ifstream input(argv[1]);

    if (!input)
    {
        cerr << "Can't read " << argv[1] << '\n';
        return 1;
    }

    bool endLabelFound = false;
    bool verbOpened = false;
    size_t nEmptyLines = 0;
    bool topLines = true;

    smatch result;
    regex labelPatterns("(" R"(^//\+?[^[:blank:]]+$)"       ")|"
                        "(" R"(^/*\+?[^[:blank:]]+*/$)"     ")|"
                        "(" "^//=$"                         ")|"
                        "(" R"(^/\*\*/$)"                   ")"
    );

    while (true)
    {
        string line;

        if (not getline(input, line))               // get the next line
            break;

        if (                                        // saw the requested label
            line.find(label) == 0 && 
            (
                line.length() == label.size() 
                || 
                isspace(label[label.size()])
            )
        )
        {
            if (not all)
            {
                if (labelFound && label == endlabel)    // at endlabel: done
                {
                    endLabelFound = true;
                    break;
                }
    
                labelFound = true;                  // found the start-label
                label = endlabel;                   // now search endlabel
                continue;
            }
        }

        if (labelFound)
        {
            if (not verbOpened)
            {
                verbOpened = true;
                cout << vindent << "verb(" << verbendl;
            }

            if (nesting && regex_match(line, result, labelPatterns))
                continue;

                                                // blank line
            if (line.find_first_not_of(" \t") == string::npos)
            {
                ++nEmptyLines;
                continue;
            }

            if (nEmptyLines != 0)
            {
                if (not topLines)
                {
                    for (size_t count = 0; count != nEmptyLines; ++count)
                    {
                        if (nrPrefix == 0)
                            cout << '\n';
                        else
                            cout << indent << setw(2) << nrPrefix++ << ":\n";
                    }
                }
                nEmptyLines = 0;
            }

            topLines = false;

            if (nrPrefix == 0)
                cout << indent << line << '\n';
            else
                cout << indent << setw(2) << nrPrefix++ << ": " << 
                                                            line << '\n';
        }
    }

    if (not all)
    {
        if (not labelFound)
        {
            cerr << progName << ": label section not found\n";
            return 1;
        }
    
        if (not endLabelFound)
        {
            cerr << progName << ": label section not ended\n";
            return 1;
        }
    }

    cout << ")\n";                          // terminate verb(... by )
}







