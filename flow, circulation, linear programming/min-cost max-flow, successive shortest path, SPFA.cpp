/*

min-cost max-flow, successive shortest path, SPFA

http://codeforces.com/problemset/problem/321/B

*/

#include "stdafx.h"

#include<cstdio>
#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
#include<cstring>
#include<queue>
using namespace std;

typedef long long lld;
const int INF = 0x3FFFFFFF;

struct MinCost
{
	struct Edge
	{
		int v, c, w, r;
	};
	vector<vector<Edge>> E;
	int n;
	MinCost(int _n) :n(_n), E(_n) {}
	void add(int u, int v, int c, int w)
	{
		E[u].push_back({ v, c, w, (int)E[v].size() });
		E[v].push_back({ u, 0, -w, (int)E[u].size() - 1 });
	}
	vector<int> sol()
	{
		vector<int> res(2);
		while (true)
		{
			queue<int> q;
			vector<int> d(n, INF);
			vector<vector<int>> p(n, { INF, INF });
			d[0] = 0;
            //spfa
			for (q.push(0); !q.empty(); q.pop())
			{
				int u = q.front();
				for (int j = 0; j < E[u].size(); j++)
				{
					Edge &e = E[u][j];
					if (e.c>0 && d[e.v] > d[u] + e.w)
					{
						d[e.v] = d[u] + e.w;
						p[e.v] = { u, j };
						q.push(e.v);
					}
				}
			}
			if (d[n - 1] > INF / 2)
				break;
			int minc = INF;
			for (int v = n - 1; v != 0; v = p[v][0])
			{
				int u = p[v][0], t = p[v][1];
				minc = min(minc, E[u][t].c);
			}
			for (int v = n - 1; v != 0; v = p[v][0])
			{
				int u = p[v][0], t = p[v][1];
				E[u][t].c -= minc;
				E[v][E[u][t].r].c += minc;
			}
			res[0] += minc;
			res[1] += d[n - 1] * minc;
		}
		return res;
	}
};

int main()
{
	int n, m;
	scanf("%d%d", &n, &m);
	vector<pair<string, int>> en(n);
	vector<int> me(m);
	for (int i = 0; i < n; i++)
		cin >> en[i].first >> en[i].second;
	for (int i = 0; i < m; i++)
		cin >> me[i];
	MinCost mc(203);
	for (int i = 0; i < m; i++)
	{
		mc.add(0, 1 + i, 1, 0);
		mc.add(1 + i, 201, 1, 0);
	}
	mc.add(201, 202, 100, 0);
	for (int i = 0; i < n; i++)
		mc.add(101 + i, 202, 1, 0);
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			if (en[j].first == "ATK" && me[i] >= en[j].second)
				mc.add(1 + i, 101 + j, 1, -(me[i] - en[j].second));
	vector<int> res = mc.sol();
	int ans = -res[1];
	mc = MinCost(202);
	for (int i = 0; i < m; i++)
		mc.add(0, 1 + i, 1, 0);
	for (int i = 0; i < n; i++)
		mc.add(101 + i, 201, 1, 0);
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			if (en[j].first == "ATK" && me[i] >= en[j].second)
				mc.add(1 + i, 101 + j, 1, en[j].second);
			else if (en[j].first == "DEF" && me[i] > en[j].second)
				mc.add(1 + i, 101 + j, 1, me[i]);
	res = mc.sol();
	if (res[0] == n)
	{
		int sum = 0;
		for (int x : me)
			sum += x;
		ans = max(ans, sum - res[1]);
	}
	printf("%d\n", ans);
}
