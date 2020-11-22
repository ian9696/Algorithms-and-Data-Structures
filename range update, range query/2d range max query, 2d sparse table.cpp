/*

2d range max query, 2d sparse table

http://codeforces.com/problemset/problem/713/D

*/

#include<stdio.h>
#include<algorithm>
#include<math.h>
using namespace std;

int a[10][10][1000][1000] = { 0 };

int main()
{
	int n, m, t;
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
		{
			int &t = a[0][0][i][j];
			scanf("%d", &t);
			if (t)
			{
				t = (i == 0 || j == 0 ? 0 : a[0][0][i - 1][j - 1]) + 1;
				t = min(t, (i == 0 ? 0 : a[0][0][i - 1][j]) + 1);
				t = min(t, (j == 0 ? 0 : a[0][0][i][j - 1]) + 1);
			}
		}
	for (int u = 1; u <= log2(n); u++)
	{
		int u2 = pow(2, u), u3 = u2 / 2;
		for (int i = 0; i + u2 <= n; i++)
			for (int j = 0; j < m; j++)
				a[u][0][i][j] = max(a[u - 1][0][i][j], a[u - 1][0][i + u3][j]);
	}
	for (int u = 0; u <= log2(n); u++)
		for (int v = 1; v <= log2(m); v++)
		{
			int u2 = pow(2, u), u3 = u2 / 2;
			int v2 = pow(2, v), v3 = v2 / 2;;
			for (int i = 0; i + u2 <= n; i++)
				for (int j = 0; j + v2 <= m; j++)
					a[u][v][i][j] = max(a[u][v - 1][i][j], a[u][v - 1][i][j + v3]);
		}
	scanf("%d", &t);
	for (int x, y, x2, y2; t > 0; t--)
	{
		scanf("%d%d%d%d", &x, &y, &x2, &y2);
		x--, y--;
		int ans = 0;
		for (int l = 1, r = min(x2 - x, y2 - y) + 1; l < r; )
		{
			int m = (l + r) / 2;
			int x3 = x + m - 1, y3 = y + m - 1;
			int u = (int)log2(x2 - x3), u2 = pow(2, u);
			int v = (int)log2(y2 - y3), v2 = pow(2, v);
			int maxv = max(a[u][v][x3][y3], a[u][v][x2 - u2][y3]);
			maxv = max(maxv, a[u][v][x3][y2 - v2]);
			maxv = max(maxv, a[u][v][x2 - u2][y2 - v2]);
			if (maxv >= m)
				l = m + 1, ans = m;
			else
				r = m;
		}
		printf("%d\n", ans);
	}
}
