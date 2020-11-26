/*

max square in rectangle (2d grid), DP, binary search, 2d sparse table

Codeforces Round #371 (Div. 1)
D. Animals and Puzzle
https://codeforces.com/contest/713/problem/D

*/

#include<cstdio>
#include<algorithm>
using namespace std;

int a[10][10][1000][1000];

int main()
{
    int n, m, t;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
        {
            int& t = a[0][0][i][j];
            scanf("%d", &t);
            if (t)
            {
                t = (i == 0 || j == 0 ? 0 : a[0][0][i - 1][j - 1]) + 1;
                t = min(t, (i == 0 ? 0 : a[0][0][i - 1][j]) + 1);
                t = min(t, (j == 0 ? 0 : a[0][0][i][j - 1]) + 1);
            }
        }
    for (int u = 1, u2 = 1 << u; u2 <= n; u2 = 1 << (++u))
    {
        int u3 = u2 >> 1;
        for (int i = 0; i + u2 - 1 < n; i++)
            for (int j = 0; j < m; j++)
                a[u][0][i][j] = max(a[u - 1][0][i][j], a[u - 1][0][i + u3][j]);
    }
    for (int u = 0, u2 = 1 << u; u2 <= n; u2 = 1 << (++u))
        for (int v = 1, v2 = 1 << v; v2 <= m; v2 = 1 << (++v))
        {
            int u3 = u2 >> 1, v3 = v2 >> 1;
            for (int i = 0; i + u2 - 1 < n; i++)
                for (int j = 0; j + v2 - 1 < m; j++)
                    a[u][v][i][j] = max(a[u][v - 1][i][j], a[u][v - 1][i][j + v3]);
        }
    scanf("%d", &t);
    for (int x, y, x2, y2; t > 0; t--)
    {
        scanf("%d%d%d%d", &x, &y, &x2, &y2);
        x--, y--, x2--, y2--;
        int l = 1, r = min(x2 - x + 1, y2 - y + 1) + 1;
        for (; l < r; )
        {
            int m = (l + r) / 2;
            int x3 = x + m - 1, y3 = y + m - 1;
            int u = 0, v = 0;
            while (1 << (u + 1) <= x2 - x3 + 1)
                u++;
            while (1 << (v + 1) <= y2 - y3 + 1)
                v++;
            int u2 = 1 << u, v2 = 1 << v;
            int maxv = max(a[u][v][x3][y3], a[u][v][x2 - u2 + 1][y2 - v2 + 1]);
            maxv = max(maxv, a[u][v][x3][y2 - v2 + 1]);
            maxv = max(maxv, a[u][v][x2 - u2 + 1][y3]);
            if (maxv >= m)
                l = m + 1;
            else
                r = m;
        }
        printf("%d\n", l - 1);
    }
}
