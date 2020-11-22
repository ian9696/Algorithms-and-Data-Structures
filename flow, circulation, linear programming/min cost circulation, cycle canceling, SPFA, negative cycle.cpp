/*

min cost circulation, cycle canceling, SPFA, negative cycle

Combinatorial Optimization Algorithms
Minimum Cost Circulation
https://oj.nctu.edu.tw/problems/907/

*/

#include<iostream>
#include<vector>
#include<queue>
using namespace std;

typedef long long lld;

const lld INF = 1e18;

struct cycle_canceling
{
    struct edge
    {
        int y, r;
        lld u, c;
        edge(int _y, int _r, lld _u, lld _c) :y(_y), r(_r), u(_u), c(_c) {}
    };

    struct pa_data
    {
        int data[3];
        int& operator[](int i)
        {
            return data[i];
        }
    };

    int n;
    lld fl, cost;
    vector<vector<edge>> E;
    vector<vector<pa_data>> pa;

    cycle_canceling(int _n) :n(_n + 1), fl(0), cost(0), E(_n + 1)
    {
        for (int i = 1; i < n; i++)
            add_edge(0, i, INF, 0);
    }

    //index 0 for supersource
    void add_edge(int u, int v, lld f, lld c)
    {
        E[u].push_back(edge(v, E[v].size(), f, c));
        E[v].push_back(edge(u, E[u].size() - 1, 0, -c));
    }
    int SPFA()
    {
        vector<lld> d(n, INF);
        queue<int> q;
        vector<bool> inq(n);
        pa.assign(n, {});
        vector<vector<bool>> b(n, vector<bool>(n));
        d[0] = 0;
        q.push(0);
        while (!q.empty())
        {
            int x = q.front();
            q.pop();
            inq[x] = 0;
            for (int i = 0; i < E[x].size(); i++)
            {
                const edge& e = E[x][i];
                int y = e.y, c=e.c;
                if (e.u > 0 && d[y] > d[x] + c)
                {
                    d[y] = d[x] + c;
                    pa[y].push_back({ x, i, (int)pa[x].size() });
                    b[y] = b[x];
                    b[y][x] = 1;
                    if (b[y][y])
                        return y;
                    if (!inq[y])
                    {
                        inq[y] = 1;
                        q.push(y);
                    }
                }
            }
        }
        return 0;
    }
    pair<lld, lld> operator()()
    {
        int x;
        while (x = SPFA())
        {
            int a, b = x;
            lld f = INF;
            while ((a = pa[b].back()[0]) != x)
            {
                f = min(f, E[a][pa[b].back()[1]].u);
                pa[a].resize(pa[b].back()[2]);
                b = a;
            }
            f = min(f, E[a][pa[b].back()[1]].u);
            fl += f;
            b = x;
            do
            {
                a = pa[b].back()[0];
                int pai = pa[b].back()[1];
                E[a][pai].u -= f;
                E[b][E[a][pai].r].u += f;
                cost += f * E[a][pai].c;
                b = a;
            } while (b != x);
        }
        return { fl, cost };
    }
};
int main()
{
    int n, m;
    scanf("%d %d", &n, &m);
    cycle_canceling CC(n);
    while (m--)
    {
        int x, y;
        lld u, c;
        scanf("%d %d %lld %lld", &x, &y, &u, &c);
        CC.add_edge(x, y, u, c);
    }
    printf("%lld\n", CC().second);
}
