#include "lexical.h"


// TYPE
bool isType(const string& str)
{
    const vector<string> types{ "int", "float", "char", "bool" };
    for (const auto& type : types)
        if (type == str)
            return true;
    return false;
}

// INTEGER
bool isInteger(const string& str)
{
    if (str.size() == 1)
    {
        if (isdigit(str[0]))
            return true;
        else
            return false;
    }
    else
    {
        if (str[0] == '0')
            return false;
        else if (str[0] == '-')
        {
            for (int i = 1; i < str.size(); i++)
            {
                if (!isdigit(str[i]))
                    return false;
            }
            return true;
        }
        else
        {
            for (int i = 0; i < str.size(); i++)
            {
                if (!isdigit(str[i]))
                    return false;
            }
            return true;
        }
    }
}

// STRING
bool isString(const string& str)
{
    return (str[0] == '"' && str[str.size() - 1] == '"');
}

// CHARACTER
bool isCharacter(const string& str)
{
    if (str.size() == 3)
    {
        if (str[0] == '\'' && str[2] == '\'')
            return true;
    }
    return false;
}

// BOOL STRING
bool isBoolstring(const string& str)
{
    return str == "true" || str == "false";
}

// FLOAT
bool isFloat(const string& str)
{
    int dot_count = 0;
    int dot_index = 0;
    if (str[0] == '-')
    {
        if (str[1] == '0' && isdigit(str[2]))
            return false;
        if (str[1] == '.' || str[str.size() - 1] == '.')
            return false;
        else
        {
            for (int i = 1; i < str.size(); i++)
            {
                if (str[i] != '.' && !isdigit(str[i]))
                    return false;

                if (str[i] == '.')
                {
                    dot_count++;
                    dot_index = i;
                }
                if (i - dot_index == 7)
                    return false;
            }
        }
        if (dot_count != 1) return false;
        else return true;
    }
    else if (isdigit(str[0]))
    {
        if (str[0] == '0' && isdigit(str[1]))
            return false;
        if (str[str.size() - 1] == '.')
            return false;
        else
        {
            for (int i = 1; i < str.size(); i++)
            {
                if (str[i] != '.' && !isdigit(str[i]))
                    return false;

                if (str[i] == '.')
                {
                    dot_count++;
                    dot_index = i;
                }
                if (i - dot_index == 7)
                    return false;
            }
        }
        if (dot_count != 1) return false;
        else return true;
    }
    else return false;
}

// ID
bool isID(const string& str)
{
    if (isdigit(str[0]))
        return false;
    else if (isalpha(str[0]) || str[0] == '_')
    {
        for (int i = 1; i < str.size(); i++)
        {
            if (!(isdigit(str[i]) || isalpha(str[i]) || str[i] == '_'))
                return false;
        }
    }
    else 
        return false;

    return true;
}


// KEYWORD
bool isKeyword(const string& str)
{
    const vector<string> keywords{ "if", "else", "while", "for", "return", "main", "printf",
        "scanf" };
    for (const auto& keyword : keywords)
        if (keyword == str)
            return true;

    return false;
}

// ARITHMETIC
bool isArithmetic(const string& str)
{
    const vector<string> arithmetics{ "*=", "/=", "++", "+=", "--", "*", "+", "-", "/", "-=" };
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

// 토큰을 입력받고 토큰밸류와 내용을 반환해줍니다.
string tokenRole(const string& token)
{
    if (isType(token))
        return "( Type : \'" + token + "\' )";
    else if (isKeyword(token))
        return "( Keyword : \'" + token + "\' )";
    else if (isBitwise(token))
        return "( Bitwise : \'" + token + "\' )";
    else if (isInteger(token))
        return "( Integer : \'" + token + "\' )";
    else if (isArithmetic(token))
        return "( Arithmetic : \'" + token + "\' )";
    else if (isComparison(token))
        return "( Comparison : \'" + token + "\' )";
    else if (isAssignment(token))
        return "( Assignment : \'" + token + "\' )";
    else if (isSeparator(token))
        return "( Separator : \'" + token + "\' )";
    else if (isFloat(token))
        return "( Float : \'" + token + "\' )";
    else if (isBoolstring(token))
        return "( Boolstring : \'" + token + "\' )";
    else if (isString(token))
        return "( String : \'" + token + "\' )";
    else if (isID(token))
        return "( Identifier : \'" + token + "\' )";
    else if (isCharacter(token))
        return "( Character : \'" + token + "\' )";
    else
        return "( !!!!!Error!!!!! Cannot read token : \'" + token + "\' )";
}

// 파일명을 입력받고 '파일명.out.txt'을 생성하고 토큰들을 저장합니다.
void lexicalAnalyzer(const string& inputFile)
{
    char ch;
    string buffer;
    ifstream input(inputFile, fstream::in);
    ofstream output(inputFile + ".out.txt");
    
    output << "--------------------------" << endl;
    if (!input.is_open())
    {
        cout << "error while opening the file\n";
        exit(0);
    }

    // string 을 인식하기 위한 변수
    int startString = 0;
    while (input >> noskipws >> ch)
    {
        // " 을 받으면 string이 시작하는 것이므로 변수에 1을 더해줍니다.
        if (ch == '"') startString += 1;

        // 첫번째 '"'가 나오면 띄어쓰기를 포함하여 buffer에 저장합니다.
        if (startString == 1) {
            buffer += ch;
            continue;
        }

        // 두번째 '"'가 나오면 그동안 buffer에 저장된 값을 String으로 출력합니다.
        else if (startString == 2) {
            buffer += ch;
            output << tokenRole(buffer) << endl;
            output << "--------------------------" << endl;
            startString = 0;
            buffer = "";
            continue;
        }

        // Whitespace를 만나면 토큰을 나누어줍니다.
        if (isWhitespace(string(1, ch)))
        {
            if (!buffer.empty())
            {
                output << tokenRole(buffer) << endl;
                output << "--------------------------" << endl;
                buffer = "";
            }
            continue;

        }

        // Arithmetic를 만나면 토큰을 나누어줍니다.
        if (isArithmetic(string(1, ch)))
        {
            if (!buffer.empty() && !isArithmetic(buffer))
            {
                output << tokenRole(buffer) << endl;
                output << "--------------------------" << endl;
                buffer = "";
            }
        }

        // Bitwise를 만나면 토큰을 나누어줍니다.
        if (isBitwise(string(1, ch)))
        {
            if (!buffer.empty() && !isBitwise(buffer))
            {
                output << tokenRole(buffer) << endl;
                output << "--------------------------" << endl;
                buffer = "";
            }
        }

        // Comparison를 만나면 토큰을 나누어줍니다.
        if (isComparison(string(1, ch)))
        {
            if (!buffer.empty() && !isComparison(buffer))
            {
                output << tokenRole(buffer) << endl;
                output << "--------------------------" << endl;
                buffer = "";
            }
        }

        // Separator를 만나면 토큰을 나누어줍니다. Separator도 하나의 토큰으로서 같이 출력해줍니다.
        if (isSeparator(string(1, ch)))
        {
            if (!buffer.empty())
            {
                output << tokenRole(buffer) << endl;
                output << "--------------------------" << endl;
                buffer = "";
            }
            if (isSeparator(string(1, ch)))
            {
                output << tokenRole(string(1, ch)) << endl;
                output << "--------------------------" << endl;
                continue;
            }
        }
        buffer += ch;
    }
    input.close();
    output.close();
}