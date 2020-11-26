/*

min cycle mean, Karp

Introduction to Algorithms (Fall 2018)
Assignment 20 - Minimum Cycle Mean (0 points, for practice only)
https://oj.nctu.edu.tw/problems/730/

*/

#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;

typedef long long lld;

const lld INF = (1LL << 62) - 1;

struct edge
{
    int u, v, c;
    void read()
    {
        scanf("%d%d%d", &u, &v, &c);
    }
};

int main()
{
    int n, m;
    scanf("%d%d", &n, &m);

    vector<edge> E(m);
    for (int i = 0; i < m; i++)
        E[i].read();

    vector<vector<lld>> d(n + 1, vector<lld>(n + 1, INF));
    d[0][1] = 0;
    for (int i = 1; i <= n; i++)
        for (const edge& e : E)
            if (d[i - 1][e.u] != INF)
                d[i][e.v] = min(d[i][e.v], d[i - 1][e.u] + e.c);

    double ans = INF;
    for (int i = 1; i <= n; i++)
    {
        double tmp = -INF;
        if (d[n][i] == INF)
            continue;
        for (int j = 0; j < n; j++)
            if (d[j][i] != INF)
                tmp = max(tmp, (d[n][i] - d[j][i]) / (double)(n - j));
        ans = min(ans, tmp);
    }
    printf("%.12f\n", ans);
}
