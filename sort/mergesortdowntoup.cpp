#include <iostream>
using namespace std;
const int N = 1e5 + 10;
int n;
int a[N];
// 自底向上归并
template <typename T>
void merge(T arr[], int l, int mid, int r)
{
    T *tmp = new T[r - l + 1];
    for (int i = l; i <= r; i++)
    {
        tmp[i - l] = arr[i];
    }
    int i = l, j = mid + 1;
    for (int k = l; k <= r; k++)
    {
        if (i > mid)
        {
            arr[k] = tmp[j - l];
            j++;
        }
        else if (j > r)
        {
            arr[k] = tmp[i - l];
            i++;
        }
        else if (tmp[i - l] < tmp[j - l])
        {
            arr[k] = tmp[i - l];
            i++;
        }
        else
        {
            arr[k] = tmp[j - l];
            j++;
        }
    }
    delete[] tmp;
}

template <typename T>
void mergesort(T arr[], int n)
{
    for (int size = 1; size <= n; size *= 2)
    {
        for (int i = 0; i + size < n; i += 2 * size)
        {
            merge(arr, i, i + size - 1, min(i + 2 * size - 1, n - 1));
        }
    }
}

int main()
{
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    mergesort(a, n);
    for (int i = 0; i < n; i++)
    {
        cout << a[i] << " ";
    }

    return 0;
}