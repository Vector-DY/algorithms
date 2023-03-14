#include <iostream>
using namespace std;

void quick_sort(int q[], int l, int r)
{
    if (l >= r)
    {
        return;
    }
    int i = l - 1, j = r + 1, mid = q[(l + r) >> 1];
    while (i < j)
    {
        do
            i++;
        while (q[i] < mid);
        do
            j--;
        while (q[j] > mid);
        if (i < j)
        {
            swap(q[i], q[j]);
        }
    }
    quick_sort(q, l, j);
    quick_sort(q, j + 1, r);
}

int main()
{
    int a[10] = {0, 10, 9, 55, 49, 3, 2, 19, -1, 99};

    quick_sort(a, 0, 9);

    for (int i = 0; i < 10; i++)
    {
        cout << a[i] << " ";
    }

    return 0;
}