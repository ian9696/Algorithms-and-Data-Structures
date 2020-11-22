/*

subtree size, DP on edge

http://codeforces.com/problemset/problem/708/C

*/

#include"stdafx.h"

#include<stdio.h>
#include<algorithm>
#include<vector>
#include<map>
using namespace std;

int n, n2;
vector<vector<int>> E;
vector<map<int, int>> siz;
vector<vector<vector<int>>> sor;
vector<map<int, int>> dp;

void dfs(int u, int p)
{
	int sum = 0;
	for (int v : E[u])
	if (v != p)
		dfs(v, u), siz[u][v] = n - siz[v][u], sum += siz[u][v];
	siz[u][p] = n - sum - 1;
	siz[u][-1] = 0;
	for (pair<int, int> pa : siz[u])
		sor[u].push_back({ pa.second, pa.first });
	sort(sor[u].rbegin(), sor[u].rend());
}

int sol2(int u, int p)
{
	if (dp[u].find(p) == dp[u].end())
	{
		int &res = dp[u][p];
		int big = sor[u][0][1] == p ? 1 : 0;
		if (sor[u][big][0] <= n2)
			res = n - siz[u][p] - sor[u][big][0];
		else
			res = n - siz[u][p] - sor[u][big][0] + sol2(sor[u][big][1], u);
	}
	return dp[u][p];
}

bool sol(int u)
{
	if (sor[u][0][0] <= n2)
		return true;
	return sol2(sor[u][0][1], u) <= n2;
}

int main()
{
	scanf("%d", &n);
	n2 = n / 2;
	E.resize(n + 1);
	siz.resize(n + 1);
	sor.resize(n + 1);
	dp.resize(n + 1);
	for (int i = 0, u, v; i < n - 1; i++)
	{
		scanf("%d%d", &u, &v);
		E[u].push_back(v);
		E[v].push_back(u);
	}
	dfs(1, -1);
	for (int i = 1; i <= n; i++)
		printf("%d%s", sol(i) ? 1 : 0, i == n ? "\n" : " ");
}
