#include <iostream>
#include <vector>
#include <functional>
using namespace std;

vector<vector<string>> partition(string s) {
    int n = s.size();
    vector<vector<bool>> f(n, vector<bool>(n, true));
    vector<vector<string>> ans;
    vector<string> path;
    function<void(int)> dfs = [&](int i) {
        if (i == n) {
            ans.push_back(path);
            return ;
        }
        for (int j = i; j < n; j++) {
            if (f[i][j]) {
                path.push_back(s.substr(i, j - i + 1));
                dfs(j + 1);
                path.pop_back();
            }
        }
    };
    for (int i = n - 1; i >= 0; i--) {
        for (int j = i + 1; j < n; j++) {
            f[i][j] = (s[i] == s[j]) && f[i + 1][j - 1];
        }
    }
    dfs(0);
    return ans;
}

int main()
{
    auto a = partition("aab");

    for (int i = 0; i < a.size(); i++) {
        for (auto it = a[i].begin(); it != a[i].end(); it++) {
            cout << *it << endl;
        }
    }
    return 0;
}