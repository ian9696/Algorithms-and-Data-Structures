
#include "stdafx.h"

#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
#include<string.h>
using namespace std;

typedef long long ll;
const int INF = 0x3FFFFFFF;
const ll INF2 = 0x3FFFFFFFFFFFFFFFLL;

struct Edge
{
	int fr, to, c, f, ind;
	Edge(int fr, int to, int c, int f, int ind)
		:fr(fr), to(to), c(c), f(f), ind(ind){}
};

int k, n;
char s[30000];
vector<vector<Edge>> adj;
vector<int> e, h;
queue<int> q;
vector<bool> act;
vector<int> cnt;

void addEdge(int u, int v)
{
	adj[u].push_back(Edge(u, v, 1, 0, adj[v].size()));
	adj[v].push_back(Edge(v, u, 0, 0, adj[u].size() - 1));
}

void enqueue(int u)
{
	if (e[u] > 0 && !act[u])
	{
		q.push(u);
		act[u] = true;
	}
}

void push(Edge &edge)
{
	int u = edge.fr, v = edge.to;
	int d = min(e[u], edge.c - edge.f);
	if (d == 0 || h[u] != h[v] + 1)
		return;
	edge.f += d;
	adj[v][edge.ind].f -= d;
	e[u] -= d;
	e[v] += d;
	enqueue(v);
}

void gap(int k)
{
	for (int i = 1; i <= 2 * n; i++)
	if (h[i] >= k)
	{
		cnt[h[i]]--;
		h[i] = max(h[i], 2 * n + 1);
		cnt[h[i]]++;
	}
}

void relabel(int u)
{
	cnt[h[u]]--;
	h[u] = INF;
	for (Edge &edge : adj[u])
	if (edge.f<edge.c)
		h[u] = min(h[u], h[edge.to] + 1);
	cnt[h[u]]++;
}

void discharge(int u)
{
	for (int i = 0; e[u] > 0 && i < adj[u].size(); i++)
		push(adj[u][i]);
	if (e[u]>0)
	{
		if (cnt[h[u]] == 1)
			gap(h[u]);
		else
			relabel(u);
		enqueue(u);
	}
}

void go(vector<int> &t, int u)
{
	t.push_back(u);
	if (u == 2)
		return;
	for (int i = 0; i < adj[u].size(); i++)
	if (adj[u][i].f == 1)
	{
		go(t, adj[u][i].to - n);
		break;
	}
}

bool cmp(const vector<int> &l, const vector<int> &r)
{
	for (int i = 0; i < l.size() && i < r.size(); i++)
	if (l[i] != r[i])
		return l[i] < r[i];
	return l.size() < r.size();
}

int main()
{
	for (int cases = 1; scanf("%d%d", &k, &n) && n; cases++)
	{
		adj = vector<vector<Edge>>(2 * n + 1);
		for (int i = 1; i <= n; i++)
		{
			scanf("\n%[^\n]", s);
			//printf("s=%s len(s)=%d\n", s, strlen(s));
			char *p = strtok(s, " ");
			while (p != NULL)
			{
				int v = atoi(p);
				if (v != 1 && i != 2)
					addEdge(i, v + n);
				p = strtok(NULL, " ");
			}
		}
		for (int i = 1; i <= n; i++)
			addEdge(i + n, i);
		adj[2 + n].back().c = INF;
		e = h = vector<int>(2 * n + 1, 0);
		h[1] = 2 * n;
		act = vector<bool>(2 * n + 1, false);
		act[1] = act[2] = true;
		cnt = vector<int>(2 * (2 * n), 0);
		cnt[2 * n] = 1;
		cnt[0] = 2 * n - 1;
		for (Edge &edge : adj[1])
		{
			int d = edge.c;
			int v = edge.to;
			edge.f += d;
			adj[v][edge.ind].f -= d;
			e[1] -= d;
			e[v] += d;
			enqueue(v);
		}
		/*
		for (int i = 1; i <= 2 * n; i++)
		{
		printf("%d : ", i);
		for (Edge &edge : adj[i])
		printf("%d:%d, ", edge.to, edge.c);
		printf("\n");
		}
		*/
		while (!q.empty())
		{
			int u = q.front();
			q.pop();
			act[u] = false;
			discharge(u);
			/*
			printf("discharge %d\n", u);
			for (int i = 1; i <= 2 * n; i++)
			{
			printf("%d : ", i);
			for (Edge &edge : adj[i])
			printf("%d:%d, ", edge.to, edge.f);
			printf("\n");
			}
			*/
		}
		/*
		for (int i = 1; i <= 2 * n; i++)
		printf("%d:%d, ", i, h[i]);
		printf("\n");
		printf("-e[1] : %d\n", -e[1]);
		*/
		printf("Case %d:\n", cases);
		if (-e[1] < k)
		{
			printf("Impossible\n\n");
			continue;
		}
		vector<vector<int>> rt;
		for (int i = 0; i < adj[1].size() && rt.size() < k; i++)
		{
			if (adj[1][i].f == 1)
			{
				rt.push_back(vector<int>());
				rt.back().push_back(1);
				go(rt.back(), adj[1][i].to - n);
			}
		}
		sort(rt.begin(), rt.end(), cmp);
		for (int i = 0; i < rt.size(); i++)
		{
			for (int j = 0; j < rt[i].size(); j++)
				printf("%d%s", rt[i][j], j == rt[i].size() - 1 ? "\n" : " ");
		}
		printf("\n");
	}

	system("pause");
	return 0;
}
