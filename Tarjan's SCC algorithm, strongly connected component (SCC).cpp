/*

Tarjan's SCC algorithm, strongly connected component (SCC)

O(n+m)

*/

#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;

const int N = 100000;

int cnt = 1;
vector<int> E[N + 1], stack;
int used[N + 1], low[N + 1], com[N + 1];

void tarjan(int u)
{
	used[u] = low[u] = cnt++;
	stack.push_back(u);
	for (int v : E[u])
	{
		if (!used[v])
			tarjan(v);
		if (!com[v])
			low[u] = min(low[u], low[v]);
	}
	if (used[u] == low[u])
	{
		int flag = 1;
		while (flag)
		{
			flag = stack.back() != u;
			com[stack.back()] = u;
			stack.pop_back();
		}
	}
}

int main()
{
	int n, m;
	scanf("%d%d", &n, &m);
	for (int i = 1, u, v; i <= m; i++)
		scanf("%d%d", &u, &v), E[u].push_back(v);
	for (int i = 1; i <= n; i++)
		if (!used[i])
			tarjan(i);
	for (int i = 1; i <= n; i++)
		printf("i=%d com[i]=%d\n", i, com[i]);
}
