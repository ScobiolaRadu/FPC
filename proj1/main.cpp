#include <bits/stdc++.h>

using namespace std;

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

bool isPunctuator(string s)
{
    string punctuators[10] = {",", ";", "(", ")", "[", "]", "{", "}", ":"};

    for(int i=0; i<9; i++)
        if(s==punctuators[i])
            return true;
    return false;
}

void lex(const string& s)
{
    const char* p = s.c_str();
    int k = 1;

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
        while (*p != '\0' && *p != ' ' && *p != '\t' && *p != '\n')
        {
            p++;
            len_w++;
        }

        string word(st_w, len_w);

        if(isKeyword(word))
        {
            cout <<"Token: "<< word <<" Type: keyword "<<"Pointer: "<< static_cast<const void*>(st_w)<<" Line: " <<k<<endl;
        }

        else if(isLiteral(word))
        {
            cout <<"Token: "<< word <<" Type: literal "<<"Pointer: "<< static_cast<const void*>(st_w)<<" Line: " <<k<<endl;
        }

        else if(isOperator(word))
        {
            cout <<"Token: "<< word <<" Type: operator "<<"Pointer: "<< static_cast<const void*>(st_w)<<" Line: " <<k<<endl;
        }

        else if(isIdentifier(word))
        {
            cout <<"Token: "<< word <<" Type: identifier "<<"Pointer: "<< static_cast<const void*>(st_w)<<" Line: " <<k<<endl;
        }

        else if (isPunctuator(word))
        {
            cout <<"Token: "<< word <<" Type: punctuator "<<"Pointer: "<< static_cast<const void*>(st_w)<<" Line: " <<k<<endl;
        }

        else
        {
            cout<<"Lexical error at : "<<word<<" Pointer: "<<static_cast<const void*>(st_w)<<" Line: "<<k<<endl;
        }

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
    file="date.in";
    //cin>>file;

    str = readFile(file);

    lex(str);

    return 0;
}
