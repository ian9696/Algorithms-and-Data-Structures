/*

lowest common ancestor (LCA), sparse table

Competitive Programming 1 (Spring 2018)
Assignment 18 (Week 13) - Chocolate
https://oj.nctu.edu.tw/problems/489/

*/

#include<cstdio>
#include<algorithm>
#include<vector>

using namespace std;

#define x first
#define y second

const int N = 20;

vector<vector<int>> p, h;

int lca(int u, int v)
{
	if (h[N - 1][u] > h[N - 1][v])
		swap(u, v);
	for (int i = N - 1; i >= 0; i--)
		if (h[N - 1][p[i][v]] >= h[N - 1][u])
			v = p[i][v];
	for (int i = N - 1; i >= 0; i--)
		if (p[i][u] != p[i][v])
			u = p[i][u], v = p[i][v];
	return u == v ? u : p[0][u];
}

int main()
{
	int n, m;
	scanf("%d%d", &n, &m);
	p.assign(N, vector<int>(n));
	h.assign(N, vector<int>(n, 1));
	scanf("%*d");
	for (int i = 1; i < n; i++)
		scanf("%d", &p[0][i]), p[0][i]--;
	h[0][0] = 0;
	for (int i = 1; i < N; i++)
		for (int j = 0; j < n; j++)
		{
			p[i][j] = p[i - 1][p[i - 1][j]];
			h[i][j] = h[i - 1][j] + h[i - 1][p[i - 1][j]];
		}
	for (int x, y, z; m > 0; m--)
	{
		scanf("%d%d%d", &x, &y, &z);
		x--, y--, z--;
		vector<pair<int, int>> tmp{ {h[N - 1][x], x}, { h[N - 1][y], y }, { h[N - 1][z], z } };
		sort(tmp.begin(), tmp.end());
		x = tmp[0].y, y = tmp[1].y, z = tmp[2].y;
		int u = lca(x, y), v = lca(x, z);
		int ans = (h[N - 1][x] + 1) + (h[N - 1][y] + 1) - (h[N - 1][u] + 1);
		if (h[N - 1][v] <= h[N - 1][u])
			v = lca(y, z);
		ans += (h[N - 1][z] + 1) - (h[N - 1][v] + 1);
		printf("%d\n", ans);
	}
}
