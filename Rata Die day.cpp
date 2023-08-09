#include <iostream>
#include <vector>
using namespace std;

int rdn(int y, int m, int d) {
    if (m < 3) {
        y--;
        m += 12;
    }

    return 365 * y + y / 4 - y / 100 + y / 400 + (153 * m - 457) / 5 + d - 306;
}

int solution(string date1, string date2) {
    int y1, y2, m1, m2, d1, d2;
    int time1, time2;
    if (!date1.empty() && !date2.empty()) {
        time1 = stoi(date1);
        time2 = stoi(date2);
        if (time1 > time2) {
            swap(time1, time2);
        }
        y1 = time1 / 10000, m1 = time1 / 100 % 100, d1 = time1 % 100;
        y2 = time2 / 10000, m2 = time2 / 100 % 100, d2 = time2 % 100;
        return rdn(y2, m2, d2) - rdn(y1, m1, d1);
    }
    return 0;
}

int main()
{
    string a1 = "20230809";
    string a2 = "20230806";
    cout << solution(a1, a2) << endl;
    return 0;
}