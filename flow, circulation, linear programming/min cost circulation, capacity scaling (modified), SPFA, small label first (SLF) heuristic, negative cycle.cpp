/*

min cost circulation, capacity scaling (modified), SPFA, small label first (SLF) heuristic, negative cycle cycle

Combinatorial Optimization Algorithms
Minimum Cost Circulation
https://oj.nctu.edu.tw/problems/907/

*/

#include<iostream>
#include<vector>
#include<queue>
using namespace std;

#define x first
#define y second
#define MXN 205

typedef long long lld;

const int INF = 1e9;

struct capacity_scaling
{
    struct edge
    {
        int y, r, u, c;
        edge(int _y, int _r, int _u, int _c) :y(_y), r(_r), u(_u), c(_c) {}
    };

    vector<edge> E[MXN];
    int n;
    int d[MXN], pa[MXN], pai[MXN], inq[MXN], vis[MXN];
    int gamma;
    lld cost, fl;

    capacity_scaling(int _n) :n(_n), gamma(0), cost(0), fl(0) {}

    //index 0 for supersource
    void add_edge(int x, int y, int u, int c)
    {
        E[x].push_back({ y, (int)E[y].size(), u, c });
        E[y].push_back({ x, (int)E[x].size() - 1, 0, -c });
        gamma = max(gamma, u);
    }
    int SPFA()
    {
        fill(d, d + n + 1, INF);
        fill(inq, inq + n + 1, 0);
        fill(vis, vis + n + 1, 0);
        queue<int> q;
        d[0] = 0;
        q.push(0);
        while (!q.empty())
        {
            //small label first (SLF) heuristic
            if (d[q.front()] > d[q.back()])
                swap(q.front(), q.back());
            int x = q.front();
            q.pop();
            inq[x] = 0;
            for (int i = 0; i < E[x].size(); i++)
            {
                const edge& e = E[x][i];
                int y = e.y, c = e.c;
                if (e.u >= gamma && d[y] > d[x] + c)
                {
                    pa[y] = x;
                    pai[y] = i;
                    d[y] = d[x] + c;
                    vis[y]++;
                    if (vis[y] > max(n / 4, 20))
                        return y;
                    if (!inq[y])
                    {
                        q.push(y);
                        inq[y] = 1;
                    }
                }
            }
        }
        return 0;
    }

    pair<lld, lld> operator()()
    {
        while (gamma)
        {
            int x;
            while (x = SPFA())
            {
                fill(vis, vis + n + 1, 0);
                while (!vis[x])
                {
                    vis[x] = 1;
                    x = pa[x];
                }
                int a, b = x, tf = INF, c = 0;
                do
                {
                    a = pa[b];
                    int l = pai[b];
                    c += E[a][l].c;
                    tf = min(tf, E[a][l].u);
                    b = a;
                } while (b != x);
                do
                {
                    a = pa[b];
                    int l = pai[b];
                    E[a][l].u -= tf;
                    E[b][E[a][l].r].u += tf;
                    b = a;
                } while (b != x);
                cost += (lld)tf * c;
                fl += tf;
            }
            gamma /= 2;
        }
        return { fl, cost };
    }
};

int main()
{
    int n, m;
    scanf("%d %d", &n, &m);
    capacity_scaling CF(n + 1);
    for (int i = 1; i <= n; i++)
        CF.add_edge(0, i, INF, 0);
    for (int i = 1; i <= m; i++)
    {
        int x, y, u, c;
        scanf("%d %d %d %d", &x, &y, &u, &c);
        CF.add_edge(x, y, u, c);
    }
    printf("%lld\n", CF().y);
}
