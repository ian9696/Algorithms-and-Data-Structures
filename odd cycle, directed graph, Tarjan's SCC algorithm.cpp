/*

odd cycle, directed graph, Tarjan's SCC algorithm

2015 Asia Daejeon Regionals
Odd Cycle
http://vjudge.net/problem/UVALive-7231

*/

#include "stdafx.h"

#include<stdio.h>
#include<algorithm>
#include<vector>
using namespace std;

int cnt;
vector<vector<int>> E;
vector<int> com, used, low, stack;

void tarjan(int x)
{
	low[x] = used[x] = cnt++;
	stack.push_back(x);
	for (int u : E[x])
	{
		if (!used[u])
			tarjan(u);
		if (!com[u])
			low[x] = min(low[x], low[u]);
	}
	if (used[x] == low[x])
	{
		while (stack.back() != x)
			com[stack.back()] = x, stack.pop_back();
		com[stack.back()] = x, stack.pop_back();
	}
}

bool dfs(int x, int t)
{
	used[x] = 1;
	stack.push_back(x);
	if (x == t)
		return true;
	for (int u : E[x])
	{
		if (!used[u])
			if (dfs(u, t))
				return true;
	}
	stack.pop_back();
	return false;
}

int main()
{
	int T;
	for (scanf("%d", &T); T > 0; T--)
	{
		int n, m;
		scanf("%d%d", &n, &m);
		int N = 2 * n;
		E.assign(N + 1, {});
		for (int j = 0, u, v; j < m; j++)
			scanf("%d%d", &u, &v), E[u].push_back(v + n), E[u + n].push_back(v);
		cnt = 1;
		com.assign(N + 1, 0);
		used.assign(N + 1, false);
		low.resize(N + 1);
		stack.clear();
		for (int i = 1; i <= N; i++)
			if (!used[i])
				tarjan(i);
		used.assign(N + 1, false);
		for (int i = 1; i <= n; i++)
			if (com[i] == com[i + n])
			{
				dfs(i, i + n);
				break;
			}
		if (stack.size() == 0)
		{
			printf("-1\n");
			continue;
		}
		for (int &x : stack)
			x = (x - 1) % n + 1;
		vector<int> ind(n + 1, -1), stack2;
		for (int x : stack)
		{
			if (ind[x] != -1)
			{
				if ((stack2.size() - ind[x]) % 2)
				{
					printf("1\n%d\n", stack2.size() - ind[x]);
					for (int i = ind[x]; i < stack2.size(); i++)
						printf("%d\n", stack2[i]);
					break;
				}
				else
				{
					while (stack2.back() != x)
						stack2.pop_back();
					stack2.pop_back();
				}
			}
			ind[x] = stack2.size();
			stack2.push_back(x);
		}
	}
}
