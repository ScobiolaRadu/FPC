#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <set>
#include <regex>

using namespace std;
// a
unordered_map<string, vector<string>> productions;
set<string> nonTerminals;
set<string> terminals;

unordered_map<string, set<string>> first;
unordered_map<string, set<string>> follow;

void read(string f)
{
    ifstream file(f);
    string line;
    while (getline(file, line))
    {
        nonTerminals.insert(line.substr(0, line.find(" -> ")));
        string init = line.substr(0, line.find(" -> "));

        size_t pos = line.find(" -> ");
        string delimeter = " | ";
        string subProd;
        string production = line.substr(pos + 4, line.length());
        pos = 0;

        while ((pos = production.find(delimeter)) != string::npos)
        {
            subProd = production.substr(0, pos);
            productions[line.substr(0, line.find(" -> "))].push_back(subProd);
            production.erase(0, pos + delimeter.length());
        }

        productions[line.substr(0, line.find(" -> "))].push_back(production);

        for (auto it = productions[line.substr(0, line.find(" -> "))].begin(); it != productions[line.substr(0, line.find(" -> "))].end(); it++)
        {
            string c;
            c = *it;
            for (int i = 0; i < c.length(); i++)
                if (c[i] >= 'a' && c[i] <= 'z')
                {
                    terminals.insert(string(1, c[i]));
                }
        }
    }
}

string findFirst(string X)
{
    for (auto it = terminals.begin(); it != terminals.end(); it++)
    {
        if (*it == X)
        {
            first[X].insert(X);
        }
    }
    string c2 = "";
    for (auto it = productions[X].begin(); it != productions[X].end(); it++)
    {

        char c = (*it)[0];

        if (c >= 'a' && c <= 'z')
        {
            first[X].insert(string(1, c));
            c2 += c;
        }

        if (c == '$')
        {
            first[X].insert(string(1, c));
            c2 += c;
        }

        if (c >= 'A' && c <= 'Z')
        {
            string t = findFirst(string(1, c));
            c2 += t;
            for (int i = 0; i < c2.length(); i++)
                first[X].insert(string(1, c2[i]));
        }
    }
    return c2;
}

string findFollow(string X)
{
    if (X == "S")
    {
        char c = '$';
        follow[X].insert(string(1, c));
    }

    for (auto it = productions.begin(); it != productions.end(); it++)
    {
        for (auto it2 = it->second.begin(); it2 != it->second.end(); it2++)
        {
            string c = *it2;
            for (int i = 0; i < c.length(); i++)
                if (X[0] == c[i])
                {
                    if (i == c.length() - 1)
                    {
                        string t;
                        for (auto it3 = follow[it->first].begin(); it3 != follow[it->first].end(); it3++)
                        {
                            t += *it3;
                            follow[X].insert(t);
                        }
                    }
                    else
                    {
                        string t;
                        for (auto it3 = first[string(1, c[i + 1])].begin(); it3 != first[string(1, c[i + 1])].end(); it3++)
                        {
                            t += *it3;
                        }

                        if (t.find('$') != string::npos)
                        {
                            for (auto it4 = follow[it->first].begin(); it4 != follow[it->first].end(); it4++)
                            {
                                t = "";
                                t += *it4;
                                follow[X].insert(t);
                            }
                        }
                        else
                        {
                            follow[X].insert(t);
                        }
                    }
                }
        }
    }
}

// b
unordered_map<string, vector<string>> productions2;
set<string> nonTerminals2;
set<string> terminals2;

unordered_map<string, set<string>> first2;
unordered_map<string, set<string>> follow2;

void read2(string f)
{
    ifstream file(f);
    string line;
    while (getline(file, line))
    {
        nonTerminals2.insert(line.substr(0, line.find(" -> ")));
        string init = line.substr(0, line.find(" -> "));
        size_t pos = line.find(" -> ");
        string delimeter = " | ";
        string subProd;
        string production = line.substr(pos + 4, line.length());
        pos = 0;

        while ((pos = production.find(delimeter)) != string::npos)
        {
            subProd = production.substr(0, pos);
            productions2[line.substr(0, line.find(" -> "))].push_back(subProd);
            production.erase(0, pos + delimeter.length());
        }

        productions2[line.substr(0, line.find(" -> "))].push_back(production);

        auto it = productions2[init].begin();
        int n = productions2[init].size();
        int km = 0;

        while (km < n)
        {
            // cout << init << " " << n << endl;
            // cout << it[km][0] << " " << init[0] << endl;

            if (it[km][0] == init[0])
            {
                string newNonTerminal = init + "'";
                nonTerminals2.insert(newNonTerminal);
                string newProd;
                for (int i = 1; i < it[km].length(); i++)
                {
                    newProd += it[km][i];
                }

                productions2[newNonTerminal].push_back(newProd + newNonTerminal);
                productions2[newNonTerminal].push_back("$");

                int k = productions2[init].size();
                int i = 0;

                while (k)
                {
                    auto it2 = productions2[init][i];

                    if (it2[0] != init[0])
                    {
                        productions2[init].erase(productions2[init].begin() + i);
                        productions2[init].push_back(it2 + newNonTerminal);
                    }
                    else
                    {
                        i++;
                    }
                    k--;
                }
                productions2[init].erase(it);
                km--;
            }
            km++;
        }

        for (auto it = productions2[line.substr(0, line.find(" -> "))].begin(); it != productions2[line.substr(0, line.find(" -> "))].end(); it++)
        {
            string c;

            c = *it;
            for (int i = 0; i < c.length(); i++)
                if (c[i] >= 'a' && c[i] <= 'z')
                {
                    terminals2.insert(string(1, c[i]));
                }
        }
    }
}

int main()
{
    // a
    cout << "a):\n";
    read("data.in");

    for (auto it = nonTerminals.begin(); it != nonTerminals.end(); it++)
    {
        findFirst(*it);
    }

    for (auto it = terminals.begin(); it != terminals.end(); it++)
    {
        findFirst(*it);
    }

    for (auto it = nonTerminals.begin(); it != nonTerminals.end(); it++)
    {
        findFollow(*it);
    }

    cout << "First: " << endl;
    for (auto it = first.begin(); it != first.end(); it++)
    {
        cout << it->first << " : { ";
        for (auto it2 = it->second.begin(); it2 != it->second.end(); it2++)
        {
            cout << *it2 << " ";
        }
        cout << '}' << endl;
    }

    cout << "Follow: " << endl;
    for (auto it = follow.begin(); it != follow.end(); it++)
    {
        cout << it->first << " : { ";
        for (auto it2 = it->second.begin(); it2 != it->second.end(); it2++)
        {
            cout << *it2 << " ";
        }
        cout << '}' << endl;
    }

    // b
    cout << "b):\n";
    read2("data2.in");

    for (auto it = nonTerminals2.begin(); it != nonTerminals2.end(); it++)
    {
        cout << *it << " -> ";
        auto it2 = productions2[*it].begin();
        cout << *it2;
        for (auto it2 = productions2[*it].begin() + 1; it2 != productions2[*it].end(); it2++)
        {
            cout << " | " << *it2;
        }
        cout << endl;
    }

    return 0;
}
