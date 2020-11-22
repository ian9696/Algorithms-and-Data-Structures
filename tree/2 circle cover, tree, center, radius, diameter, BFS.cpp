/*

2 circle cover, tree, center, radius, diameter, BFS

Competitive Programming 1 (Spring 2018)
Assignment 21 (Week 15) - Bombing
https://oj.nctu.edu.tw/problems/492/

*/

#include<cstdio>
#include<algorithm>
#include<vector>
#include<queue>

using namespace std;

#define x first
#define y second

int main()
{
	int n;
	scanf("%d", &n);
	vector<pair<int, int>> edg(n - 1);
	for (int i = 0, u, v; i < n - 1; i++)
		scanf("%d%d", &edg[i].x, &edg[i].y), edg[i].x--, edg[i].y--;
	vector<int> ans;
	int minval = n;
	for (int i = 0; i < n - 1; i++)
	{
		vector<vector<int>> E(n);
		vector<int> tmp;
		for (int j = 0; j < n - 1; j++)
			if (j != i)
			{
				E[edg[j].x].push_back(edg[j].y);
				E[edg[j].y].push_back(edg[j].x);
			}
        int val=0, s=0;
		for (int k = 0; k < 2; k++)
			for (int l = 0, t; l < 2; l++)
			{
				vector<int> p(n, -1), d(n, -1);
				queue<int> Q;
				p[s] = s, d[s] = 0;
				for (Q.push(s); !Q.empty(); Q.pop())
				{
					int u = t = Q.front();
					for (int v : E[u])
						if (p[v] == -1)
							p[v] = u, d[v] = d[u] + 1, Q.push(v);
				}
				if (l == 0)
					s = t;
				else
				{
					val = max(val, d[t]);
					for (int j = 0, dt = d[t]; j < dt / 2; j++)
						t = p[t];
					tmp.push_back(t);
					for (int j = 0; j < n; j++)
						if (p[j] == -1)
							s = j;
				}
			}
		if (val < minval)
			minval = val, ans = tmp;
	}
	ans[0]++, ans[1]++;
	minval=(minval+1)/2;
	printf("%d %d %d\n", ans[0], ans[1], minval);
}
