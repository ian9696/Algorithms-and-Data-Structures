
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

int n, m;
VLL e;
VI h;
VI cnt;
queue<int> q;
vector<bool> act;
vector<vector<Edge>> adj;

void addEdge(int fr, int to, int c)
{
	adj[fr].push_back(Edge(fr, to, c, 0, adj[to].size()));
	if (fr == to)
		adj[fr].back().ind++;
	adj[to].push_back(Edge(to, fr, c, 0, adj[fr].size() - 1));
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
	int d = min(e[u], (ll)edge.c - edge.f);
	if (d == 0 || h[u] <= h[v])
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
	for (int i = 1; i <= n; i++)
	if (h[i] >= k)
	{
		cnt[h[i]]--;
		h[i] = max(h[i], n + 1);
		cnt[h[i]]++;
	}
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

int main()
{
	scanf("%d%d", &n, &m);
	e = VLL(n + 1, 0);
	h = VI(n + 1, 0);
	cnt = VI(2 * n, 0);
	act = vector<bool>(n + 1, false);
	adj = vector<vector<Edge>>(n + 1);

	e[1] = INF2;
	h[1] = n;
	cnt[n] = 1;
	cnt[0] = n - 1;
	act[1] = act[n] = true;
	for (int i = 0; i < m; i++)
	{
		int a, b, c;
		scanf("%d%d%d", &a, &b, &c);
		addEdge(a, b, c);
	}
	for (Edge &edge : adj[1])
		push(edge);
	while (!q.empty())
	{
		int u = q.front();
		q.pop();
		act[u] = false;
		discharge(u);
	}
	ll ans = 0;
	for (Edge &edge : adj[1])
		ans += edge.f;
	printf("%lld\n", ans);

	return 0;
}

/*

4 9
1 2 13
2 3 4
1 1 3
3 1 8
2 2 5
3 4 3
2 2 1
3 4 7
4 3 3

*/