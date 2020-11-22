
#include "stdafx.h"

#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;

typedef long long ll;
const int INF = 0x3FFFFFFF;
const ll INF2 = 0x3FFFFFFFFFFFFFFFLL;

struct Edge
{
	int fr, to, c, f, ind;
	Edge(int _fr, int _to, int _c, int _f, int _ind)
		:fr(_fr), to(_to), c(_c), f(_f), ind(_ind){}
};

int p, t, s, c;
vector<vector<Edge>> adj;
vector<int> e, h;
queue<int> q;
vector<bool> act;
vector<int> cnt;

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
	int d = min(e[edge.fr], edge.c - edge.f);
	if (d == 0 || h[edge.fr] != h[edge.to] + 1)
		return;
	edge.f += d;
	adj[edge.to][edge.ind].f -= d;
	e[edge.fr] -= d;
	e[edge.to] += d;
	enqueue(edge.to);
}

void relabel(int u)
{
	cnt[h[u]]--;
	h[u] = INF;
	for (Edge &edge : adj[u])
	if (edge.f < edge.c)
		h[u] = min(h[u], h[edge.to] + 1);
	cnt[h[u]]++;
}

void gap(int k)
{
	for (int i = 0; i < p + t + 2; i++)
	{
		if (h[i] < k)
			continue;
		cnt[h[i]]--;
		h[i] = max(h[i], p + t + 3);
		cnt[h[i]]++;
	}
}

void discharge(int u)
{
	for (int i = 0; e[u] > 0 && i<adj[u].size(); i++)
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

int main()
{
	int k;
	scanf("%d", &k);
	while (k--)
	{
		scanf("%d%d%d%d", &p, &t, &s, &c);
		vector<vector<int>> pos(p + t + 1, vector<int>(2));
		for (int i = 1; i <= p + t; i++)
			scanf("%d%d", &pos[i][0], &pos[i][1]);
		adj = vector<vector<Edge>>(p + t + 2);
		for (int i = 1; i <= p; i++)
		for (int j = p + 1; j <= p + t; j++)
		if (200 * (abs(pos[i][0] - pos[j][0]) + abs(pos[i][1] - pos[j][1])) <= c*s)
		{
			adj[i].push_back(Edge(i, j, 1, 0, adj[j].size()));
			adj[j].push_back(Edge(j, i, 0, 0, adj[i].size() - 1));
		}
		for (int i = 1; i <= p; i++)
		{
			adj[0].push_back(Edge(0, i, 1, 0, adj[i].size()));
			adj[i].push_back(Edge(i, 0, 0, 0, adj[0].size() - 1));
		}
		for (int i = p + 1; i <= p + t; i++)
		{
			adj[i].push_back(Edge(i, p + t + 1, 1, 0, adj[p + t + 1].size()));
			adj[p + t + 1].push_back(Edge(p + t + 1, i, 0, 0, adj[i].size() - 1));
		}
		e = h = vector<int>(p + t + 2, 0);
		h[0] = p + t + 2;
		act = vector<bool>(p + t + 2, false);
		act[0] = act[p + t + 1] = true;
		cnt = vector<int>(2 * (p + t + 2), 0);
		cnt[p + t + 2] = 1;
		cnt[0] = p + t + 1;
		for (Edge &edge : adj[0])
		{
			int d = edge.c;
			edge.f += d;
			adj[edge.to][edge.ind].f -= d;
			e[0] -= d;
			e[edge.to] += d;
			enqueue(edge.to);
		}
		while (!q.empty())
		{
			int u = q.front();
			q.pop();
			act[u] = false;
			discharge(u);
		}
		int ans = -e[0];
		/*
		printf("      ");
		for (int i = 0; i < p + t + 2; i++)
		printf("%3d ", i);
		printf("\n");
		for (int i = 0; i < p + t + 2; i++)
		{
		printf("%3d : ", i);
		for (int j = 0; j < p + t + 2; j++)
		printf("%3d ", f[i][j]);
		printf("\n");
		}
		*/
		/*
		for (int i = 0; i < p + t + 2; i++)
		{
		printf("%3d : ", i);
		for (Edge &edge : adj[i])
		printf("to %3d f %3d, ", edge.to, edge.f);
		printf("\n");
		}
		*/
		printf("%d\n", ans);
	}

	system("pause");
	return 0;
}
