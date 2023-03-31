#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct Token
{
    string s;
    int len_w;
    int line;
    char* pointer;
};


bool isKeyword(string s)
{
    string keywords[98]= {"alignas", "alignof", "and", "and_eq", "asm", "atomic_cancel", "atomic_commit", "atomic_noexcept", "auto",
                          "bitand", "bitor", "bool", "break", "case", "catch", "char", "char8_t", "char16_t", "char32_t", "class", "compl", "concept",
                          "const", "consteval", "constexpr", "constinit", "const_cast", "continue", "co_await", "co_return", "co_yield", "decltype", "default",
                          "delete", "do", "double", "dynamic_cast", "else", "enum", "explicit", "export", "extern", "false", "float", "for", "friend", "goto",
                          "if", "inline", "int", "long", "mutable", "namespace", "new", "noexcept", "not", "not_eq", "nullptr", "operator", "or", "or_eq", "private",
                          "protected", "public", "reflexpr", "register", "reinterpret_cast", "requires", "return", "short", "signed", "sizeof", "static",
                          "static_assert", "static_cast", "struct", "switch", "synchronized", "template", "this", "thread_local", "throw", "true", "try", "typedef",
                          "typeid", "typename", "union", "unsigned", "using", "virtual", "void", "volatile", "wchar_t", "while", "xor", "xor_eq"
                         };
    for(int i=0; i<97; i++)
        if(s == keywords[i])
            return true;
    return false;
}

bool isIdentifier(string s)
{
    if(isalnum(s[0]) || s[0] == '_')
    {
        for(int i=1; i<s.length(); i++)
            if(ispunct(s[i]) && s[i] != '_')
                return false;
    }

    else
        return false;

    return true;

}

bool isLiteral(string s)
{
    if(s[0] == '"' && s[s.length()-1] == '"')
        return true;

    for(int i=0; i<s.length(); i++)
        if(!isdigit(s[i]))
            return false;

    return true;
}

bool isOperator(string s)
{
    string operators[37] = {"++", "--", "+", "-", "*", "/", "%", "<", ">", "<=", ">=", "==", "!=",
                            "&&", "||", "!", "&", "|", "<<", ">>", "~", "^", "=", "+=", "-=", "*=", "/=", "%=",
                            "<<=", ">>=", "&=", "^=", "|=", "?:", ".", "->"
                           };

    for(int i=0; i<36; i++)
        if (s == operators[i])
            return true;
    return false;
}

bool isOperatorChar(char c)
{
    const string operators = "+-*/%<=>!&|~^?.";

    return (operators.find(c) != string::npos);
}

bool isPunctuator(string s)
{
    string punctuators[10] = {",", ";", "(", ")", "[", "]", "{", "}", ":"};

    for(int i=0; i<9; i++)
        if(s==punctuators[i])
            return true;
    return false;
}

bool isPunctuatorChar(char c)
{
    const string punctuators = ",;()[]{}:";

    return (punctuators.find(c) != string::npos);
}

vector<Token> lex(const string& s)
{
    const char* p = s.c_str();
    int k = 1;
    vector<Token> tokens;

    while (*p != '\0')
    {
        while (*p == ' ' || *p == '\t' || *p == '\n')
        {
            if (*p == '\n')
            {
                k++;
            }
            p++;
        }

        const char* st_w = p;
        int len_w = 0;

        while (*p != '\0')
        {
            if (*p == ' ' || *p == '\t' || *p == '\n' ||
                    (isOperatorChar(*p)  && *(p+1) != ' ' && *(p+1) != '\n' && *(p+1) != '\t' && *(p+1) != '\0'
                     && *(p-1) != ' ' && *(p-1) != '\n' && *(p-1) != '\t')
                    || isPunctuatorChar(*p))
            {
                break;
            }
            p++;
            len_w++;
        }

        if (len_w > 0)
        {
            Token token;
            token.s = string(st_w, len_w);
            token.len_w = len_w;
            token.line = k;
            token.pointer = const_cast<char*>(st_w);
            tokens.push_back(token);
        }

        if (isOperatorChar(*p))
        {
            const char* st_w = p;
            int len_w = 0;

            while (*p != '\0' && isOperatorChar(*p))
            {
                p++;
                len_w++;
            }

            Token token;
            token.s = string(st_w, len_w);
            token.len_w = len_w;
            token.line = k;
            token.pointer = const_cast<char*>(st_w);
            tokens.push_back(token);
        }

        if (isPunctuatorChar(*p))
        {
            const char* st_w = p;
            int len_w = 0;

            while (*p != '\0' && isPunctuatorChar(*p))
            {
                p++;
                len_w++;
            }

            Token token;
            token.s = string(st_w, len_w);
            token.len_w = len_w;
            token.line = k;
            token.pointer = const_cast<char*>(st_w);
            tokens.push_back(token);
        }
    }

    return tokens;
}


void printTokens(const vector<Token>& tokens)
{
    for (const Token& token : tokens)
    {

        if(isKeyword(token.s))
        {
            cout <<"Token: "<<token.s<<" Type: keyword";
        }

        else if(isLiteral(token.s))
        {
            cout <<"Token: "<<token.s<<" Type: literal";
        }

        else if(isOperator(token.s))
        {
            cout <<"Token: "<<token.s<<" Type: operator";
        }

        else if(isIdentifier(token.s))
        {
            cout <<"Token: "<<token.s<<" Type: identifier";
        }

        else if (isPunctuator(token.s))
        {
            cout <<"Token: "<<token.s<<" Type: punctuator";
        }

        else
        {
            cout<<"Lexical error at: "<<token.s;
        }

        cout<< " Length: "<<token.len_w<<" Pointer: "<< static_cast<void*>(token.pointer)<<" Line: " <<token.line<<endl;
    }
}


string readFile(string file)
{
    ifstream f(file);

    return
        string((istreambuf_iterator<char>(f)), istreambuf_iterator<char>());
}

int main()
{
    string str;
    string file;
    vector<Token> tokens;
    cin>>file;

    str = readFile(file);
    tokens = lex(str);

    printTokens(tokens);
    return 0;
}
