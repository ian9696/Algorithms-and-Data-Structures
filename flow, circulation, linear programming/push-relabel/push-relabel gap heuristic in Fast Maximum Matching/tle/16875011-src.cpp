
#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
#include<string.h>
using namespace std;

typedef long long ll;
const int INF = 0x3FFFFFFF;
const ll INF2 = 0x3FFFFFFFFFFFFFFFLL;
typedef vector<int> VI;
typedef vector<VI> VVI;
typedef vector<ll> VLL;
typedef vector<VLL> VVLL;

struct Edge
{
	int fr, to, c, f, ind;
	Edge(int fr, int to, int c, int f, int ind)
		:fr(fr), to(to), c(c), f(f), ind(ind){}
};

int n, m, p;
VI e, h;
VI cnt;
queue<int> q;
vector<bool> act;
vector<vector<Edge>> adj;

void addEdge(int fr, int to, int c)
{
	adj[fr].push_back(Edge(fr, to, c, 0, adj[to].size()));
	adj[to].push_back(Edge(to, fr, 0, 0, adj[fr].size() - 1));
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
	if (d <= 0 || h[u] <= h[v])
		return;
	edge.f += d;
	adj[v][edge.ind].f -= d;
	e[u] -= d;
	e[v] += d;
	enqueue(v);
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
	for (int i = 0; i < n + m + 2; i++)
	if (h[i] >= k)
	{
		cnt[h[i]]--;
		h[i] = max(h[i], n + m + 3);
		cnt[h[i]]++;
	}
}

void discharge(int u)
{
	while (e[u] > 0)
	{
		for (int i = adj[u].size() - 1; i >= 0 && e[u]>0; i--)
			push(adj[u][i]);
		if (e[u] > 0)
		{
			if (cnt[h[u]] == 1)
				gap(h[u]);
			else
				relabel(u);
		}
	}
}

int main()
{
	scanf("%d%d%d", &n, &m, &p);
	e = h = VI(n + m + 2, 0);
	e[0] = INF;
	h[0] = n + m + 2;
	cnt = VI(2 * (n + m + 2), 0);
	cnt[n + m + 2] = 1;
	cnt[0] = n + m + 1;
	act = vector<bool>(n + m + 2, false);
	act[0] = act[n + m + 1] = true;
	adj = vector<vector<Edge>>(n + m + 2);
	for (int i = 0, a, b; i < p; i++)
	{
		scanf("%d%d", &a, &b);
		addEdge(a, n + b, 1);
	}
	for (int i = 1; i <= n; i++)
		addEdge(0, i, 1);
	for (int i = n + 1; i <= n + m; i++)
		addEdge(i, n + m + 1, 1);
	for (Edge &edge : adj[0])
		push(edge);
	while (!q.empty())
	{
		int u = q.front();
		q.pop();
		act[u] = false;
		discharge(u);
		/*
		for (int i = 0; i < n + m + 2; i++)
		printf("%d:%d, ", i, h[i]);
		printf("\n");
		for (int i = 0; i < n + m + 2; i++)
		{
		printf("%d : ", i);
		for (int j = 0; j < adj[i].size(); j++)
		printf("%d:%d,  ", adj[i][j].to, adj[i][j].f);
		printf("\n");
		}
		*/
	}
	int ans = 0;
	for (Edge &edge : adj[0])
		ans += edge.f;
	printf("%d\n", ans);

	return 0;
}
