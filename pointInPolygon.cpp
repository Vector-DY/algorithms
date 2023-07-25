#include <iostream>
#include <vector>
using namespace std;
struct Point {
    double x = 0;
    double y = 0;
    Point() {
        x = 0;
        y = 0;
    }
    Point(double _x, double _y) {
        x = _x;
        y = _y;
    }
};
bool pointInPolygon(Point p, vector<Point>& Polygon, int nCount)
{
    int nCross = 0;
    for (int i = 0; i < nCount; i++) {
        Point p1 = Polygon[i];
        Point p2 = Polygon[(i + 1) % nCount];

        if (p1.y == p2.y) {
            continue;
        }
        if (p.y < min(p1.y, p2.y)) {
            continue;
        }
        if (p.y >= max(p1.y, p2.y)) {
            continue;
        }

        double x = (double)(p.y - p1.y) * (double)(p2.x - p1.x) / (double)(p2.y - p1.y) + p1.x;

        if (x > p.x) {
            nCross++;
        }
    }
    if (nCross % 2 == 1) {
        return true;
    } else {
        return false;
    }
}

int main()
{
    vector<Point> p;
    p.push_back(Point(268.28, 784.75));
	p.push_back(Point(153.98, 600.60));
	p.push_back(Point(274.63, 336.02));
	p.push_back(Point(623.88, 401.64));
	p.push_back(Point(676.80, 634.47));
	p.push_back(Point(530.75, 822.85));
	p.push_back(Point(268.28, 784.75));
    Point test1;
    Point test2;
    Point test3;
    test1.x = 407.98, test1.y = 579.43; 
    test2.x = 678.92, test2.y = 482.07;
    test3.x = 268.28, test3.y = 784.75;
    cout << pointInPolygon(test1, p, 7) << " " << pointInPolygon(test2, p, 7) << endl;
    cout << pointInPolygon(test3, p, 7) << endl;
    return 0;
}