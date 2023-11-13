/*

detect odd cycle (undirected graph, edge insertion), disjoint set (xor with parent)

Codeforces Round #360 (Div. 1)
D. Dividing Kingdom II
https://codeforces.com/contest/687/problem/D

*/

#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;

struct Edge
{
	int u, v, w, id;
	bool operator<(const Edge &r)const
	{
		return w > r.w;
	}
};

int a[1001][2];
Edge e[1000000];
int n, m, q;

int find(int x)
{
	if (a[x][0] == 0)
		return x;
	int y = find(a[x][0]);
	a[x][1] = a[a[x][0]][1] ^ a[x][1];
	return a[x][0] = y;
}
bool query(int l, int r)
{
	int x = find(l);
	int y = find(r);
	if (x == y)
	{
		if (a[l][1] != a[r][1])
			return false;
		return true;
	}
	a[x][0] = y;
	a[x][1] ^= a[l][1] ^ a[r][1] ^ 1;
	return false;
}
void clear()
{
	for (int i = 1; i <= n; i++)
		a[i][0] = a[i][1] = 0;
}

int main()
{
	scanf("%d%d%d", &n, &m, &q);
	for (int i = 0; i < m; i++)
		scanf("%d%d%d", &e[i].u, &e[i].v, &e[i].w), e[i].id = i;
	sort(e, e + m);
	for (int i = 0, l, r, p; i < q && scanf("%d%d", &l, &r); i++)
	{
		clear();
		l--, r--;
		for (p = 0; p < m; p++)
		{
			if (e[p].id >= l && e[p].id <= r && query(e[p].u, e[p].v))
				break;
		}
		printf("%d\n", p == m ? -1 : e[p].w);
	}

	return 0;
}
