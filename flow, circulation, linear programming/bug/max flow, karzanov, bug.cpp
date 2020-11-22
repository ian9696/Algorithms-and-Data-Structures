/*

max flow, karzanov, bug

https://official.contest.yandex.com/mipt2018prefinals/contest/7784/problems/C2/

*/

#include "stdafx.h"

#include<cstdio>
#include<algorithm>
#include<vector>
#include<queue>
#include<cstring>
using namespace std;

const int INF = 0x3FFFFFFF;

struct Karzanov {
	struct edge {
		int t, c, r;
		edge(int _t, int _c, int _r) : t(_t), c(_c), r(_r) {}
	};
	vector<int> l, L;
	vector<vector<edge>> e;
	vector<int> ex;
	vector<vector<vector<int>>> st;
	Karzanov(int n) : e(n + 1), ex(n + 1), st(n + 1) {}
	void add(int u, int v, int w) {//directed
		e[u].push_back(edge(v, w, e[v].size()));
		e[v].push_back(edge(u, 0, e[u].size() - 1));
		//printf("add_edge %d->%d   %d\n", u, v, w);
	}
	edge& rev(const edge& E) {
		return e[E.t][E.r];
	}
	bool bfs(int s, int t) {
		l.assign(e.size(), INF);
		l[s] = 1;
		queue<int> Q;
		for (Q.push(s); !Q.empty(); Q.pop()) {
			s = Q.front();
			L.push_back(s);
			for (const edge& E : e[s])
				if (E.c > 0 && l[E.t] > l[s] + 1) {
					l[E.t] = l[s] + 1; Q.push(E.t);
				}
		}
		return l[t] < INF;
	}
	void ch(int u, int p, int val)
	{
		int v = e[u][p].t, r = e[u][p].r;
		//printf("ch %d %d -> %d   %d\n", u, p, v, val);
		e[u][p].c -= val;
		e[v][r].c += val;
		ex[u] -= val;
		ex[v] += val;
	}
	void push(int u, int p, int val)
	{
		if (!val)
			return;
		int v = e[u][p].t, r = e[u][p].r;
		//printf("push %d %d -> %d   %d\n", u, p, v, val);
		ch(u, p, val);
		st[v].push_back({ u, p, val });
	}
	int operator()(int s, int t) {
		//printf("s=%d t=%d\n", s, t);
		int ans = 0;
		for (; bfs(s, t); )
		{
			vector<bool> dead(l.size()), in(l.size());
			while (L.back() != t)
				L.pop_back();
			L.pop_back();
			reverse(L.begin(), L.end());
			L.pop_back();
			reverse(L.begin(), L.end());
			for (int u : L)
				in[u] = 1;
			in[s] = in[t] = 1;

			for (int i = 0; i < e[s].size(); i++)
				push(s, i, e[s][i].c);
			while (1)
			{
				for (int u : L)
				{
					if (dead[u] || ex[u] <= 0)
						continue;
					for (int i = 0; i < e[u].size() && ex[u]>0; i++)
					{
						edge& E = e[u][i];
						if (E.c > 0 && l[u] + 1 == l[E.t] && !dead[E.t] && in[E.t]) {
							int val = min(ex[u], E.c);
							push(u, i, val);
							if (E.t == t)
								ans += val;
						}
					}
				}
				int u = -1;
				for (auto it = L.rbegin(); it != L.rend(); it++)
					if (!dead[*it] && ex[*it] > 0)
					{
						u = *it;
						break;
					}
				if (u == -1)
					break;
				while (ex[u] > 0)
				{
					int v = st[u].back()[0], p = st[u].back()[1];
					int val = min(ex[u], st[u].back()[2]);
					ch(v, p, -val);
					st[u].back()[2] -= val;
					if (st[u].back()[2] == 0)
						st[u].pop_back();
				}
				dead[u] = 1;
			}
			L.clear();
			ex.assign(l.size(), 0);
			st.assign(l.size(), vector<vector<int>>());
		}
		return ans;
	}
};

pair<int, int> token(char* s)
{
	char v;
	int n;

	sscanf(s, "%c%d", &v, &n);

	return{ v == 'x', n };
}

int main()
{
	int n, k;
	scanf("%d %d", &n, &k);

	char s[30000];
	scanf("%s", s);

	vector<pair<int, int>> v;
	vector<pair<int, int>> vv;

	for (char* p = strtok(s, "+"); p; p = strtok(NULL, "+"))
	{
		char *t;
		if (t = strchr(p, '*'))
		{
			*t = 0;
			vv.push_back({ token(p).second, token(t + 1).second });
		}
		else
		{
			v.push_back(token(p));
		}
	}

	Karzanov D(n * 2 + 2 + 2);
	int S = 0, T = n * 2 + 2 + 1;

	for (int i = 1; i <= n; i++)
	{
		D.add(S, i, 1);
		D.add(n + i + 1, T, 1);
	}

	D.add(S, n + 1, k - n);
	D.add(T - 1, T, k - n);

	for (int i = 0; i < v.size(); i++)
	{
		if (v[i].first == 1)
			D.add(v[i].second, T - 1, 1);
		else
			D.add(n + 1, n + v[i].second + 1, 1);
	}

	for (int i = 0; i < vv.size(); i++)
	{
		D.add(vv[i].first, n + 1 + vv[i].second, 1);
	}

	//printf("%d\n", D(S, T));

	if (k >= n && k <= 2 * n && D(S, T) == k)
		puts("NO");
	else
		puts("YES");


	return 0;
}
