#include <iostream>
using namespace std;
/*
给你一个日期，请你设计一个算法来判断它是对应一周中的哪一天。

输入为三个整数：day、month 和 year，分别表示日、月、年。

您返回的结果必须是这几个值中的一个 {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"}。

给出的日期一定是在 1971 到 2100 年之间的有效日期。
*/


class Solution {
    const string weekdays[7] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
public:
    string dayOfTheWeek(int day, int month, int year) {
        tm dt = {0, 0, 0, day, month - 1, year - 1900};
        time_t t = mktime(&dt);

        return weekdays[localtime(&t)->tm_wday];
    }
};


int main()
{
    Solution s;
    cout << s.dayOfTheWeek(31, 8, 2019) << endl;

    return 0;
}