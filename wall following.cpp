/*

wall following

ACM-ICPC 2017 Asia Tsukuba Regional
proglem G - Go around the Labyrinth
https://vjudge.net/contest/177902#problem/G
http://icpc.iisf.or.jp/2017-tsukuba/

*/

#include<cstdio>

const int N = 50;

char s[N + 2];
int n, m, a[N + 2][N + 2], tr[4][2] = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} }, cnt;

bool in(int x, int y)
{
	return x >= 0 && x < n && y >= 0 && y < m;
}

bool sol(int x, int y, int d)
{
	if (!x && !y  && cnt == 4)
		return 1;
	if (!in(x, y) || !a[x][y])
		return 0;
	a[x][y] = 0;
	if ((!x || x == n - 1) && (!y || y == m - 1))
		cnt++;
	for (int i = 1; i >= -1; i--)
	{
		int t = (d + i + 4) % 4;
		if (sol(x + tr[t][0], y + tr[t][1], t))
			return 1;
	}
	if ((!x || x == n - 1) && (!y || y == m - 1))
		cnt--;
	return 0;
}

int main()
{
	for (; scanf("%d%d", &n, &m) && (n || m); )
	{
		for (int i = 0; i < n; i++)
		{
			scanf("%s", s);
			for (int j = 0; j < m; j++)
				a[i][j] = s[j] == '.';
		}
		cnt = 0;
		printf("%s\n", sol(0, 0, 1) ? "YES" : "NO");
	}
}
