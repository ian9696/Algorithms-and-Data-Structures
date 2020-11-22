
#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;

typedef long long ll;
const int INF = 0x3FFFFFFF;
const ll INF2 = 0x3FFFFFFFFFFFFFFFLL;

struct node
{
	int u;
	node *n;
	node(int _u, node *_n) :u(_u), n(_n){}
};

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
		vector<vector<int>> adj(p + t + 2);
		for (int i = 1; i <= p; i++)
		for (int j = p + 1; j <= p + t; j++)
		if (200 * (abs(pos[i][0] - pos[j][0]) + abs(pos[i][1] - pos[j][1])) <= c*s)
		{
			ca[i][j] = 1;
			adj[i].push_back(j);
		}
		for (int i = 1; i <= p; i++)
		{
			ca[0][i] = 1;
			f[0][i] = 1;
			f[i][0] = -f[0][i];
			e[0] -= 1;
			e[i] += 1;
			adj[i].push_back(0);
		}
		for (int i = p + 1; i <= p + t; i++)
		{
			ca[i][p + t + 1] = 1;
			adj[i].push_back(p + t + 1);
		}
		h[0] = p + t + 2;
		node *fnt = NULL, *cur = NULL, *pre = NULL;
		for (int i = 1; i <= p + t; i++)
			fnt = new node(i, fnt);
		cur = fnt;
		while (cur != NULL)
		{
			int u = cur->u;
			bool rel = false;
			while (e[u] > 0)
			{
				if (sc[u] >= adj[u].size())
				{
					rel = true;
					int minh = INF;
					for (int w : adj[u])
						minh = min(minh, h[w]);
					h[u] = minh + 1;
					sc[u] = 0;
				}
				int v = adj[u][sc[u]];
				if (h[u] == h[v] + 1)
				{
					if (f[v][u] == ca[v][u])
						adj[v].push_back(u);
					int d = min(e[u], ca[u][v] - f[u][v]);
					f[u][v] += d;
					f[v][u] = -f[u][v];
					e[u] -= d;
					e[v] += d;
					if (f[u][v] == ca[u][v])
					for (int i = 0; i < adj[u].size(); i++)
					if (adj[u][i] == v)
						adj[u].erase(adj[u].begin() + i);
				}
				else
					sc[u]++;
			}
			if (rel && cur != fnt)
			{
				pre->n = cur->n;
				cur->n = fnt;
				fnt = cur;
				pre = NULL;
			}
			pre = cur;
			cur = cur->n;
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

	return 0;
}
