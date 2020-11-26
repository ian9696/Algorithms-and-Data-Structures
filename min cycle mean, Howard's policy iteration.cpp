/*

min cycle mean, Howard's policy iteration

Introduction to Algorithms (Fall 2018)
Assignment 20 - Minimum Cycle Mean (0 points, for practice only)
https://oj.nctu.edu.tw/problems/730/

*/

#include<cstdio>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;

typedef long long lld;

const lld INF = (1LL << 62) - 1;
const double EPS = 1e-6;

struct edge
{
    int u, v, c;
    void read()
    {
        scanf("%d%d%d", &u, &v, &c);
    }
};

struct howard
{
    int n;
    vector<edge> e;
    vector<double> d;
    vector<int> c, p;

    howard(int _n, const vector<edge> &_e) : n(_n), e(_e), d(n + 1, INF), c(n + 1), p(n + 1)
    {
    }

    double operator()()
    {
        for (const edge& E : e)
        {
            if (d[E.u] > E.c)
            {
                d[E.u] = c[E.u] = E.c;
                p[E.u] = E.v;
            }
        }

        for (int cnt = 1000; ; cnt--)
        {
            double ld;
            int s;
            get_cycle(ld, s);
            reverse_bfs(ld, s);

            if (!improve(ld) || cnt == 1)
                return ld;
        }
    }

    void get_cycle(double& ld, int& s)
    {
        ld = INF;
        s = 0;
        vector<int> vis(n + 1, 0);
        vector<lld> dis(n + 1, 0);

        for (int i = 1; i <= n; i++)
        {
            vis[i] = !vis[i] ? 1 : -1;

            for (int u = i; vis[u] >= 0; u = p[u])
            {
                int v = p[u];
                if (!vis[v])
                {
                    vis[v] = vis[u] + 1;
                    dis[v] = dis[u] + c[u];
                }
                else if (vis[v] > 0)
                {
                    double len = (double)(dis[u] + c[u] - dis[v]) / (vis[u] + 1 - vis[v]);
                    if (ld > len)
                    {
                        ld = len;
                        s = u;
                    }
                    break;
                }
            }

            for (int u = i; vis[u] >= 0; u = p[u])
                vis[u] = -1;
        }
    }

    void reverse_bfs(double ld, int s)
    {
        vector<vector<int>> pre(n + 1);
        for (int i = 1; i <= n; i++)
            if (i != s)
                pre[p[i]].push_back(i);

        queue<int> Q;
        for (Q.push(s); !Q.empty(); Q.pop())
        {
            int v = Q.front();
            for (int u : pre[v])
            {
                d[u] = d[v] + c[u] - ld;
                Q.push(u);
            }
        }
    }

    bool improve(double ld)
    {
        bool ans = false;
        for (const edge& E : e)
        {
            double nd = d[E.v] + E.c - ld;
            double dt = d[E.u] - nd;
            if (dt > 0)
            {
                ans |= dt > EPS;
                d[E.u] = nd;
                c[E.u] = E.c;
                p[E.u] = E.v;
            }
        }
        return ans;
    }
};

int main()
{
    int n, m;
    scanf("%d%d", &n, &m);

    vector<edge> E(m);
    for (int i = 0; i < m; i++)
        E[i].read();

    double ans = howard(n, E)();
    printf("%.12f\n", ans);
}
