/*

2d submatrix swap, linked list, array

http://codeforces.com/problemset/problem/706/E

*/

#include "stdafx.h"

#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;

int a[1002 * 1002][3];

void mov(int &p, int h, int w)
{
	for (int i = 1; i <= h; i++)
		p = a[p][0];
	for (int i = 1; i <= w; i++)
		p = a[p][1];
}

void get(int &p, int h, int w, vector<pair<int, int>> &res)
{
	for (int i = 1; i <= max(h, w); i++)
		p = h ? a[p][0] : a[p][1], res.push_back({ p, h>0 });
}

int main()
{
	int n, m, q;
	scanf("%d%d%d", &n, &m, &q);
	vector<int> r(n + 2);
	for (int i = 0; i <= n + 1; i++)
	{
		for (int j = 0; j <= m + 1; j++)
		{
			int x = i*(m + 2) + j;
			a[x][0] = x + (m + 2);
			a[x][1] = x + 1;
		}
		r[i] = i*(m + 2);
	}
	for (int i = 1; i <= n; i++)
		for (int j = 1, val; j <= m; j++)
			scanf("%d", &a[i*(m + 2) + j][2]);
	for (int x, y, u, v, h, w; q > 0; q--)
	{
		scanf("%d%d%d%d%d%d", &x, &y, &u, &v, &h, &w);
		vector<pair<int, int>> ch, to;
		int p3, p4;
		p3 = p4 = r[0];
		mov(p3, x - 1, y - 1);
		mov(p4, u - 1, v - 1);
		for (int i = 0, p, p2; i < 2; i++)
		{
			swap(p3, p4);

			p = p3, p2 = p4;
			mov(p2, 0, 1);
			get(p, h, 0, ch);
			get(p2, h, 0, to);
			get(p, 0, w, ch);
			get(p2, 1, 0, to);
			get(p2, 0, w - 1, to);

			p = p3, p2 = p4;
			mov(p2, 1, 0);
			get(p, 0, w, ch);
			get(p2, 0, w, to);
			get(p, h, 0, ch);
			get(p2, 0, 1, to);
			get(p2, h - 1, 0, to);
		}
		for (int i = 0; i < ch.size(); i++)
			a[ch[i].first][ch[i].second] = to[i].first;
	}
	for (int i = 1; i <= n; i++)
		for (int j = 1, p = r[i]; j <= m; j++)
			p = a[p][1], printf("%d%s", a[p][2], (j == m ? "\n" : " "));
}
