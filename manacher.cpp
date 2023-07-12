#include <iostream>
/*
Longest Palindrome Problem
*/
using namespace std;
/*
Center Extension Method
*/
pair<int, int> expand(const string& s,int left, int right) {
    while (left >= 0 && right < s.size() && s[left] == s[right]) {
        left --;
        right++;
    }
    return {left + 1, right - 1};
}

string longestP(string s) {
    int st = 0, ed = 0;
    for (int i = 0; i < s.size(); i++) {
        auto [l1, r1] = expand(s, i, i);
        auto [l2, r2] = expand(s, i, i + 1);
        if (r1 - l1 > ed - st) {
            ed = r1;
            st = l1;
        }
        if (r2 - l2 > ed - st) {
            ed = r2;
            st = l2;
        }
    }
    return s.substr(st, ed - st + 1);
}
/*
manacher 算法 详解参考https://www.cnblogs.com/cloudplankroader/p/10988844.html
*/
int manacher(string str) {
    if (str.size() == 0) {
        return 0;
    }
    // 预处理 arr记录字符串 p记录回文半径
    int len = (int)(str.length() * 2 + 1);
    char *arr = new char[len];
    int *p = new int[len];
    int index = 0;
    for (int i = 0; i < len; i++) {                           
        arr[i] = (i & 1) == 0 ? '#' : str[index++];   
    }
    // R 最右回文边界，C为R对应的最左回文中心，maxn是记录的最大回文半径
    int R = -1, C = -1, maxn = 0;
    for (int i = 0; i < len; i++) {
        // 先取最短回文半径，i > R 时为1，反之为i对应的i'的回文半径或i到R的距离
        p[i] = R > i ? min(R - i, p[2 * C - i]) : 1;
        // 取最小值后从边界匹配，匹配失败后退出
        while (i + p[i] < len && i - p[i] > -1) {
            if (arr[i + p[i]] == arr[i - p[i]]) {
                p[i]++;
            } else {
                break;
            }
        }
        // 更新R C
        if (i + p[i] > R) {
            R = i + p[i];
            C = i;
        }
        // 更新最大回文半径值
        maxn = max(maxn, p[i]);
    }
    // 资源销毁
    delete[] arr;
    delete[] p;
    return maxn - 1;


}

int main()
{
    cout << longestP("babad") << endl;
    cout << manacher("abbbca") << endl;
    cout << manacher("caabbbaad") << endl;
    return 0;
}