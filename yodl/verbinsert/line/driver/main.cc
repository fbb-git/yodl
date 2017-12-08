#include "main.ih"

int main(int argc, char **argv)
{
    Line line;

    cout << hex;

    while (true)
    {
        cout << "(en)target: ";
        string target;
        getline(cin, target);

        line.setTarget(target);
        while (true)
        {
            cout << "line: ";
            switch (line.next())
            {
                case Line::EMPTY:
                    cout << "empty\n";
                break;
        
                case Line::TEXT:
                    cout << "text\n";
                break;
        
                case Line::TARGET:
                    cout << "target\n";
                break;
        
                case Line::ENDTARGET:
                    cout << "endtarget\n";
                break;

                default:
                    cout << "not handled: ";
                break;
            }
            cout << (unsigned int)line.type() << '\n';
        }
    }
        
}
