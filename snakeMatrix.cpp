#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
int n,m;
const int N = 110;
int res[N][N];
int dx[4] = {0,1,0,-1},dy[4] = {1,0,-1,0};

int main()
{
    scanf("%d%d", &n, &m);
    
    for (int x = 0, y = 0, k = 1, d = 0; k <= n * m; k++) {
        res[x][y] = k;
        int a = x + dx[d],b = y + dy[d];
        if (a < 0 || a >= n || b < 0 || b >= m || res[a][b]) {
            d = (d + 1) % 4;
            a = x + dx[d],b = y + dy[d];
        }
        x = a,y = b;
    }
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d ", res[i][j]);
        }
        cout<<endl;
    }
    return 0;
}