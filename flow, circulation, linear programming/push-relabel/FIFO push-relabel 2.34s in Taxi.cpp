
#include "stdafx.h"

#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;

typedef long long ll;
const int INF = 0x3FFFFFFF;
const ll INF2 = 0x3FFFFFFFFFFFFFFFLL;

void enqueue(int u, queue<int> &q, vector<bool> &act, vector<int> &e)
{
	if (e[u] > 0 && !act[u])
	{
		q.push(u);
		act[u] = true;
	}
}

int main()
{
	int k;
	scanf("%d", &k);
	while ((k--) > 0)
	{
		int p, t, s, c;
		scanf("%d%d%d%d", &p, &t, &s, &c);
		vector<vector<int>> pos(p + t + 1, vector<int>(2));
		for (int i = 1; i <= p + t; i++)
			scanf("%d%d", &pos[i][0], &pos[i][1]);
		vector<vector<int>> ca(p + t + 2, vector<int>(p + t + 2, 0));
		vector<vector<int>> f = ca;
		vector<int> e(p + t + 2, 0), h(p + t + 2, 0), sc(p + t + 1, 0);
		vector<int> list(p + t + 1);
		vector<vector<int>> adj(p + t + 1);
		queue<int> q;
		vector<bool> act(p + t + 2, false);
		int cur = 0;
		for (int i = 1; i <= p; i++)
		for (int j = p + 1; j <= p + t; j++)
		if (200 * (abs(pos[i][0] - pos[j][0]) + abs(pos[i][1] - pos[j][1])) <= c*s)
		{
			ca[i][j] = 1;
			adj[i].push_back(j);
			adj[j].push_back(i);
		}
		for (int i = 1; i <= p; i++)
		{
			ca[0][i] = 1;
			f[0][i] = 1;
			f[i][0] = -f[0][i];
			e[0] -= 1;
			e[i] += 1;
			adj[i].push_back(0);
			enqueue(i, q, act, e);
		}
		for (int i = p + 1; i <= p + t; i++)
		{
			ca[i][p + t + 1] = 1;
			adj[i].push_back(p + t + 1);
		}
		h[0] = p + t + 2;
		for (int i = 1; i <= p + t; i++)
			list[i] = i;
		act[0] = act[p + t + 1] = true;
		while (!q.empty())
		{
			int u = q.front();
			q.pop();
			act[u] = false;
			while (e[u] > 0)
			{
				if (sc[u] == adj[u].size())
				{
					int minh = INF;
					for (int w : adj[u])
					if (f[u][w] < ca[u][w])
						minh = min(minh, h[w]);
					h[u] = minh + 1;
					sc[u] = 0;
				}
				int v = adj[u][sc[u]];
				if (f[u][v] < ca[u][v] && h[u] == h[v] + 1)
				{
					int d = min(e[u], ca[u][v] - f[u][v]);
					f[u][v] += d;
					f[v][u] = -f[u][v];
					e[u] -= d;
					e[v] += d;
					enqueue(v, q, act, e);
				}
				else
					sc[u]++;
			}
		}
		int ans = 0;
		for (int i = 1; i <= p; i++)
			ans += f[0][i];
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
		printf("%d\n", ans);
	}

	system("pause");
	return 0;
}
