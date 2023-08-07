#include <iostream>
#include <vector>
#include <functional>
using namespace std;


int main() 
{
    ios::sync_with_stdio(false);
    int n;
    cin >> n;
    vector<int> a(n);
    vector<int> tmp(n);
    int res;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    function<void(int, int, vector<int>&)> merge_sort = [&](int l, int r, vector<int>& q) {
        if (l >= r) {
            return ;
        }
        int mid = (l + r) >> 1;
        merge_sort(l, mid, q);
        merge_sort(mid + 1, r, q);

        int k = 0, lptr = l, rptr = mid + 1;
        while (lptr <= mid && rptr <= r) {
            if (q[lptr] <= q[rptr]) {
                tmp[k++] = q[lptr++];
            } else {
                tmp[k++] = q[rptr++];
                res += (mid - lptr + 1);
            }
        }
        while (lptr <= mid) {
            tmp[k++] = q[lptr++];
        }
        while (rptr <= r) {
            tmp[k++] = q[rptr++];
        }

        for (int i = l, j = 0; i <= r; i++, j++) {
            q[i] = tmp[j];
        }
    };
    merge_sort(0, n - 1, a);
    cout << res << endl;
    for (int i = 0; i < n; i++) {
        cout << a[i] << " ";
    } 
    return 0;
} 