#include <iostream>
#include <vector>
#include <string>
using namespace std;
vector<string> split(string &str, char target)
{
    vector<string> res;
    string s(str);
    int pos = 0;
    while (pos < s.size())
    {
        while (pos < s.size() && s[pos] == target)
        {
            pos++;
        }
        int start = pos;
        while (pos < s.size() && s[pos] != target)
        {
            pos++;
        }
        if (pos > start)
        {
            res.emplace_back(s.substr(start, pos - start));
        }
    }
    return res;
}
int main()
{
    string a;
    getline(cin, a);
    auto t = split(a, ' ');
    for (int i = 0; i < t.size(); i++)
    {
        cout << t[i] << endl;
    }
    return 0;
}