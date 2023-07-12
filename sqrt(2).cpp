#include <iostream>
#include <iomanip>
using namespace std;

const double R = 0.0000000001;

double sqrt2_bis() {
    double l = 1.4, r = 1.5;

    while (r - l > R) {
        double mid = (l + r) / 2;
        if (mid * mid > 2) {
            r = mid;
        } else {
            l = mid;
        }
    }
    return l;
}
double sqrt2_newton(double x) {
    if (x == 1 || x == 0) {
        return x;
    }
    double temp = x / 2;
    while(1) {
        double a = temp;
        temp = (temp + x / temp) / 2;
        if (abs(a - temp) < R) {
            return temp;
        }
    }

}


int main()
{
    cout << setprecision(8) << "二分法:" << sqrt2_bis() << endl;
    cout << setprecision(8) <<"牛顿迭代:" << sqrt2_newton(2) << endl;
    return 0;
}