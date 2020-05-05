#include "lexical.h"


// TYPE
bool isType(const string& str)
{
    const vector<string> types{ "int", "float", "string", "bool" };
    for (const auto& type : types)
        if (type == str)
            return true;
    return false;
}

// INTEGER
bool isInteger(const string& str);

// STRING
bool isString(const string& str)
{
    return str[0] == '"' && str[str.size() - 1] == '"';
}

// BOOL STRING
bool isBoolstring(const string& str)
{
    return str == "true" || str == "false";
}

// FLOAT
bool isFloat(const string& str);

// ID
bool isID(const string& str)
{
    if (isdigit(str[0]))
        return false;
    int counter = 0;
    if (str[0] == '_')
        counter++;

    for (; counter < str.size(); counter++)
        if (!(isalnum(str[counter])))
            return false;
    return true;
}


// KEYWORD
bool isKeyword(const string& str)
{
    const vector<string> keywords{ "if", "else", "while", "for", "return" };
    for (const auto& keyword : keywords)
        if (keyword == str)
            return true;

    return false;
}

// ARITHMETIC
bool isArithmetic(const string& str)
{
    const vector<string> arithmetics{ "*=", "+=", "/=", "++", "--", "*", "+", "-", "/", "-=" };
    for (const auto& arithmetic : arithmetics)
        if (arithmetic == str)
            return true;

    return false;
}

// BITWISE
bool isBitwise(const string& str)
{
    const vector<string> bitwises{ "<<", ">>", "&", "|" };
    for (const auto& bitwise : bitwises)
        if (bitwise == str)
            return true;

    return false;
}

// ASSIGMENT
bool isAssignment(const string& str)
{
    const vector<string> assignments{ "=" };
    for (const auto& assignment : assignments)
        if (assignment == str)
            return true;

    return false;
}

// COMPARISON
bool isComparison(const string& str)
{
    const vector<string> comparisons{ ">=", "<=", ">", "<", "==", "!=" };
    for (const auto& comparison : comparisons)
        if (comparison == str)
            return true;

    return false;
}

// SEPARATOR
bool isSeparator(const string& str)
{
    const vector<string> separators{ "{", "}", ",", "(", ")", ";" };
    for (const auto& separator : separators)
        if (separator == str)
            return true;

    return false;
}

// WHITESPACE
bool isWhitespace(const string& str)
{
    return str == " " || str == "\n" || str == "\t";
}

string tokenRole(const string& token)
{
    if (isType(token))
        return "( type => " + token + " )";
    else if (isKeyword(token))
        return "( keyword => " + token + " )";
    else if (isBitwise(token))
        return "( bitwise => " + token + " )";
    else if (isArithmetic(token))
        return "( arithmetic => " + token + " )";
    else if (isComparison(token))
        return "( comparison => " + token + " )";
    else if (isAssignment(token))
        return "( assignment => " + token + " )";
    else if (isSeparator(token))
        return "( separator => " + token + " )";
    //else if (isFloat(token))
    //    cout << "(float, " << token << ")" << endl;
    //else if (isInteger(token))
    //    cout << "(integer, " << token << ")" << endl;
    else if (isBoolstring(token))
        return "( boolstring => " + token + " )";
    else if (isString(token))
        return "( string => " + token + " )";
    else if (isID(token))
        return "( identifier => " + token + " )";
    else
        throw runtime_error(token);
}

void lexicalAnalyze(const string& inputFile)
{
    char ch;
    string buffer;
    ifstream input(inputFile, fstream::in);
    ofstream output(inputFile + ".out.txt");
    
    output << "------------------------" << endl;
    if (!input.is_open())
    {
        cout << "error while opening the file\n";
        exit(0);
    }

    bool miltiCm = false, singleCm = false;
    while (input >> noskipws >> ch)
    {
        if (singleCm || miltiCm)
        {
            if (singleCm && ch == '\n')
                singleCm = false;

            if (miltiCm && ch == '*')
            {
                input >> ch;
                if (ch == EOF)
                    break;

                if (ch == '/')
                    miltiCm = false;
            }
            continue;
        }

        if (isWhitespace(string(1, ch)))
        {
            if (!buffer.empty())
            {
                output << tokenRole(buffer) << endl;
                output << "------------------------" << endl;
                buffer = "";
            }
            continue;
        }

        if (isArithmetic(string(1, ch)))
        {
            if (!buffer.empty() && !isArithmetic(buffer))
            {
                output << tokenRole(buffer) << endl;
                output << "------------------------" << endl;
                buffer = "";
            }
        }

        if (isBitwise(string(1, ch)))
        {
            if (!buffer.empty() && !isBitwise(buffer))
            {
                output << tokenRole(buffer) << endl;
                output << "------------------------" << endl;
                buffer = "";
            }
        }

        if (isAssignment(string(1, ch)))
        {
            if (!buffer.empty() && !isAssignment(buffer))
            {
                output << tokenRole(buffer) << endl;
                output << "------------------------" << endl;
                buffer = "";
            }
        }

        if (isComparison(string(1, ch)))
        {
            if (!buffer.empty() && !isComparison(buffer))
            {
                output << tokenRole(buffer) << endl;
                output << "------------------------" << endl;
                buffer = "";
            }
        }

        if (isSeparator(string(1, ch)))
        {
            if (!buffer.empty())
            {
                output << tokenRole(buffer) << endl;
                output << "------------------------" << endl;
                buffer = "";
            }
            if (isSeparator(string(1, ch)))
            {
                output << tokenRole(string(1, ch)) << endl;
                output << "------------------------" << endl;
                continue;
            }
        }
        buffer += ch;
    }
    input.close();
    output.close();
}