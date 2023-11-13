/*

cut vertex (articulation point), 1-pass, O(n) space, DFS, BFS

1-pass
O(m+n) time
O(n) space

Streaming Algorithms (Spring 2018)
2. Articulation Point
https://oj.nctu.edu.tw/problems/578/

*/

#include<cstdio>
#include<algorithm>
#include<vector>
#include<queue>
#include<unordered_set>
#include<cstring>
using namespace std;

const int N = 10000;
int n, m, d;
short a[N + 1], p;
short *E[N + 1], *dfn, *low, *now;
bool *used, *cut;
unordered_set<int> edg;

void getE()
{
	for (int i = 1; i <= n; i++)
	{
		E[i] = new short[a[i]];
		a[i] = 0;
	}
	for (auto e : edg)
	{
		int u = e&(1 << 14) - 1, v = e >> 14;
		E[u][a[u]++] = v;
		E[v][a[v]++] = u;
	}
	edg.clear();
}

void bfs()
{
	getE();
	used = new bool[n + 1];
	for (int k = 0; k < 2; k++)
	{
		queue<short> Q;
		for (int i = 1; i <= n; i++)
			used[i] = 0;
		for (int i = 1; i <= n; i++)
		{
			if (used[i])
				continue;
			used[i] = 1;
			for (Q.push(i); !Q.empty(); Q.pop())
			{
				int u = Q.front();
				for (int j = 0; j < a[u]; j++)
				{
					int v = E[u][j], e = min(u, v) | max(u, v) << 14;
					auto it = edg.find(e);
					if (used[v] || it != edg.end())
						continue;
					used[v] = 1;
					Q.push(v);
					edg.insert(e);
				}
				if (k == 1)
					delete E[u];
			}
		}
	}
	delete used;
	memset(a, 0, (n + 1) * sizeof(a[0]));
	for (const int &e : edg)
		a[e&(1 << 14) - 1]++, a[e >> 14]++;
}

void dfs()
{
	short &u = now[p];
	dfn[u] = low[u] = ++d;
	bool c = 0, c2 = 0;
	for (; --a[u] >= 0; )
	{
		short &v = E[u][a[u]];
		if (dfn[v] == 0)
		{
			now[++p] = v;
			dfs();
			low[u] = min(low[u], low[v]);
			(c ? c2 : c) = 1;
			if (p > 1 && d <= low[v])
				cut[u] = 1;
		}
		else if (v != now[p - 1])
			low[u] = min(low[u], dfn[v]);
	}
	if (p == 1 && c2)
		cut[u] = 1;
	p--, d--;
}

void rem()
{
	unordered_set<int> tmp;
	edg.swap(tmp);
}

void sol()
{
	getE();
	rem();
	dfn = new short[n + 1];
	low = new short[n + 1];
	now = new short[n + 1];
	cut = new bool[n + 1];
	for (int i = 0; i <= n; i++)
		dfn[i] = low[i] = now[i] = cut[i] = 0;
	now[++p] = 1;
	dfs();

	bool none = 1;
	for (int i = 1; i <= n; i++)
		if (cut[i])
		{
			printf("%d\n", i);
			none = 0;
		}
	if (none)
		printf("None\n");
}

int sc()
{
	int x = 0, c;
	for (; '0' <= (c = getchar()) && c <= '9'; )
		x = (x << 1) + (x << 3) + c - 48;
	return x;
}

int main()
{
	for (n = sc(), m = sc(); m > 0; m--)
	{
		int u = sc(), v = sc(), t = edg.size();
		if (u != v)
			edg.insert(min(u, v) | max(u, v) << 14);
		int t2 = edg.size();
		if (t < t2)
			a[u]++, a[v]++;
		if (t2 > max(100, (n << 2) + n))
			bfs();
	}

	bfs();
	sol();
}
