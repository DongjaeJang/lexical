#include "lexical.h"

int main()
{
    string a;
    char b[20], c[20] = { 0 };
    int i = 0, j = 0;

    do {
        cout << "<< Enter the execution command of your lexical analyzer >>" << endl;
        cout << "=>ex) lexical_analyzer <input_file_name>" << endl;
        cout << "=>";
        cin >> a >> b;
    } while (a.compare("lexical_analyzer") != 0);

    lexicalAnalyzer(b);

    return 0;
}