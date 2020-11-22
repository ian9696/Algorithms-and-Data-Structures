/*

max weight independent set (MWIS), tree, DP, DFS

Competitive Programming 1 (Spring 2018)
Assignment 17 (Week 13) - Maximum Weighted Independent Set
https://oj.nctu.edu.tw/problems/488/

*/

#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;

typedef long long lld;

int n;
vector<int> w;
vector<vector<lld>> dp;//n, y
vector<vector<int>> E;

void sol(int u)
{
	for (int v : E[u])
	{
		sol(v);
		dp[u][0] += max(dp[v][0], dp[v][1]);
		dp[u][1] += dp[v][0];
	}
	dp[u][1] += w[u];
}

void get(int u, vector<int> &ans, lld &sum, int t)
{
	if (t == 0)
		for (int v : E[u])
			get(v, ans, sum, 2);
	else if (t == 1)
	{
		ans.push_back(u);
		sum += w[u];
		for (int v : E[u])
			get(v, ans, sum, 0);
	}
	else
		get(u, ans, sum, dp[u][1] >= dp[u][0]);
}

void get2(int u, vector<int> &ans, lld &sum, int t)
{
	if (t == 0)
		for (int v : E[u])
			get(v, ans, sum, 2);
	else if (t == 1)
	{
		ans.push_back(u);
		sum += w[u];
		for (int v : E[u])
			get(v, ans, sum, 0);
	}
	else
		get(u, ans, sum, dp[u][1] > dp[u][0]);
}

int main()
{
	scanf("%d", &n);
	w.resize(n + 1);
	for (int i = 1; i <= n; i++)
		scanf("%d", &w[i]);
	dp.assign(n + 1, vector<lld>(2, 0));
	E.assign(n + 1, vector<int>());
	for (int i = 1, u, v; i <= n - 1; i++)
	{
		scanf("%d%d", &u, &v);
		E[v].push_back(u);
		dp[u][0] = 1;
	}
	int s = 0;
	for (int i = 1; i <= n; i++)
		if (dp[i][0] == 0)
			s = i;
		else
			dp[i][0] = 0;
	sol(s);

	vector<int> ans, ans2;
	lld sum = 0, sum2 = 0;
	get(s, ans, sum, 2);//n, y, x
	get2(s, ans2, sum2, 2);
	sort(ans.begin(), ans.end());
	sort(ans2.begin(), ans2.end());
	printf("%lld\n", sum2);
	for (int i = 0; i < ans2.size(); i++)
		printf("%d%s", ans2[i], i + 1 == ans2.size() ? "\n" : " ");
}
