/*

max independent set, bipartite graph, Dinic

Asia Daejeon Regionals 2016
problem D - Independent Edges
https://vjudge.net/contest/173900#problem/D

*/

#include "stdafx.h"

#include<cstdio>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;

const int INF = 1e9;
const int N = 1000;

int used[N + 2], left[N + 2];
vector<int> E[N + 2];

struct Edge
{
	int t, c, r;
	Edge(int _t, int _c, int _r) :t(_t), c(_c), r(_r) {}
};

struct Dinic
{
	vector<vector<Edge>> E;
	int n;
	vector<int> d;
	Dinic(int _n) :n(_n), E(_n) {}
	void add(int u, int v, int c)
	{
		E[u].push_back(Edge(v, c, E[v].size()));
		E[v].push_back(Edge(u, 0, E[u].size() - 1));
	}
	bool bfs(int s, int t)
	{
		queue<int> Q;
		d.assign(n, INF);
		d[s] = 0;
		for (Q.push(s); !Q.empty(); Q.pop())
		{
			int u = Q.front();
			for (Edge &e : E[u])
				if (e.c > 0 && d[e.t] == INF)
				{
					d[e.t] = d[u] + 1;
					Q.push(e.t);
				}
		}
		return d[t] < INF;
	}
	int dfs(int s, int t, int rem)
	{
		if (s == t || rem == 0)
			return rem;
		int res = 0;
		for (Edge &e : E[s])
			if (e.c > 0 && d[e.t] == d[s] + 1)
			{
				int flow = dfs(e.t, t, min(e.c, rem));
				rem -= flow;
				res += flow;
				e.c -= flow;
				E[e.t][e.r].c += flow;
			}
		return res ? res : d[s] = 0;
	}
	int flow(int s, int t)
	{
		int res = 0, tmp;
		while (bfs(s, t))
			while ((tmp = dfs(s, t, INF)))
				res += tmp;
		return res;
	}
};

void dfs(int u, int l)
{
	used[u] = 1;
	left[u] = l;
	for (int v : E[u])
		if (!used[v])
			dfs(v, l ^ 1);
}

int main()
{
	int n, m;
	for (int n, m; scanf("%d%d", &n, &m) == 2; )
	{
		for (int i = 0; i < n; i++)
			used[i] = 0, E[i].clear();
		for (int i = 0; i < m; i++)
		{
			int u, v;
			scanf("%d%d", &u, &v);
			u--, v--;
			E[u].push_back(v);
			E[v].push_back(u);
		}
		for (int i = 0; i < n; i++)
			if (!used[i])
				dfs(i, 1);
		vector<int> fo(n), re(n);
		int l = 0, r;
		for (int i = 0; i < n; i++)
			if (left[i])
				fo[i] = l++;
		r = l;
		for (int i = 0; i < n; i++)
			if (!left[i])
				fo[i] = r++;
		r = n - l;
		for (int i = 0; i < n; i++)
			re[fo[i]] = i;
		int all = n + 2;
		Dinic D(all);
		for (int i = 0; i < n; i++)
			if (i<l)
				D.add(all - 2, i, 1);
			else
				D.add(i, all - 1, 1);
		Dinic D2 = D;
		for (int i = 0; i < l; i++)
			for (int j : E[re[i]])
				D.add(i, fo[j], 1);
		int flow = D.flow(all - 2, all - 1);
		printf("%d\n", flow);
		for (int i = 0; i < l; i++)
			for (Edge &e : D.E[i])
				if (e.t >= l && e.t < l + r && e.c == 0)
					printf("%d %d\n", re[i] + 1, re[e.t] + 1);
		for (int i = 0; i < l; i++)
				for (int j : E[re[i]])
					D2.add(i, fo[j], INF);
		flow = D2.flow(all - 2, all - 1);
		printf("%d\n", n - flow);
		for (int i = 0; i < n; i++)
			if ((D2.d[i] < INF) == (i < l))
				printf("%d ", re[i] + 1);
		printf("\n");
	}
}
