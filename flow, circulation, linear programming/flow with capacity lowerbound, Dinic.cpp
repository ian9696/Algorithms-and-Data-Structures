/*

flow with capacity lowerbound, Dinic

2016 Asia Daejeon Regionals
Rounding
https://icpcarchive.ecs.baylor.edu/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=5632

*/

#include<cstdio>
#include<algorithm>
#include<vector>
#include<queue>

using namespace std;

const int INF = 1e9;

struct Dinic
{
    struct Edge
    {
        int t, c, r;
        Edge(int _t, int _c, int _r) :t(_t), c(_c), r(_r) {}
    };
    vector<int> l;
    vector<vector<Edge>> E;
    Dinic(int _n) : E(_n + 1) {}
    void add(int u, int v, int w)
    {
        E[u].push_back(Edge(v, w, E[v].size()));
        E[v].push_back(Edge(u, 0, E[u].size() - 1));
    }
    Edge& rev(Edge e)
    {
        return E[e.t][e.r];
    }
    bool bfs(int s, int t)
    {
        l.assign(E.size(), INF);
        l[s] = 1;
        queue<int> Q;
        for (Q.push(s); !Q.empty(); Q.pop())
        {
            s = Q.front();
            for (const Edge& e : E[s])
                if (e.c > 0 && l[e.t] > l[s] + 1)
                {
                    l[e.t] = l[s] + 1;
                    Q.push(e.t);
                }
        }
        return l[t] < INF;
    }
    int dfs(int s, int t, int num = INF)
    {
        if (s == t || num == 0)
            return num;
        int ans = 0;
        for (Edge& e : E[s])
            if (e.c > 0 && l[e.t] == l[s] + 1)
            {
                int tmp = dfs(e.t, t, min(num, e.c));
                rev(e).c += tmp, ans += tmp;
                e.c -= tmp, num -= tmp;
            }
        return ans > 0 ? ans : l[s] = 0;
    }
    int operator()(int s, int t)
    {
        int ans = 0, tmp = 0;
        while (bfs(s, t))
            while ((tmp = dfs(s, t)))
                ans += tmp;
        return ans;
    }
};

void sol()
{
    for (int m, n; scanf("%d%d", &m, &n) == 2; )
    {
        vector<vector<int>> low(m, vector<int>(n + 1)), up(m, vector<int>(n + 1));
        for (int i = 0; i < m; i++)
            for (int j = 0, l, r; j <= n; j++)
            {
                scanf("%d.%d", &l, &r);
                low[i][j] = l;
                up[i][j] = l + (r > 0);
            }
        low.push_back(vector<int>(n));
        up.push_back(vector<int>(n));
        for (int j = 0, l, r; j < n; j++)
        {
            scanf("%d.%d", &l, &r);
            low[m][j] = l;
            up[m][j] = l + (r > 0);
        }
        int tot = tot = m + n + 2 + 2;
        vector<int> ex(m + n + 2, 0);
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                ex[i] -= low[i][j], ex[m + j] += low[i][j];
        for (int i = 0; i < m; i++)
            ex[i] += low[i][n], ex[tot - 4] -= low[i][n];
        for (int j = 0; j < n; j++)
            ex[m + j] -= low[m][j], ex[tot - 3] += low[m][j];
        Dinic D(tot);
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                D.add(i, m + j, up[i][j] - low[i][j]);
        for (int i = 0; i < m; i++)
            D.add(tot - 4, i, up[i][n] - low[i][n]);
        for (int j = 0; j < n; j++)
            D.add(m + j, tot - 3, up[m][j] - low[m][j]);
        for (int i = 0; i < tot - 2; i++)
            if (ex[i] > 0)
                D.add(tot - 2, i, ex[i]);
            else if (ex[i] < 0)
                D.add(i, tot - 1, -ex[i]);
        D.add(tot - 3, tot - 4, INF);
        D(tot - 2, tot - 1);
        for (int i = 0; i < m; i++)
            for (Dinic::Edge& e : D.E[i])
                if (e.t >= m && e.t < m + n)
                    low[i][e.t - m] = up[i][e.t - m] - e.c;
        for (Dinic::Edge& e : D.E[tot - 4])
            if (e.t < m)
                low[e.t][n] = up[e.t][n] - e.c;
        for (Dinic::Edge& e : D.E[tot - 3])
            if (e.t >= m && e.t < m + n)
                low[m][e.t - m] = low[m][e.t - m] + e.c;
        for (int i = 0; i < m; i++)
            for (int j = 0; j <= n; j++)
                printf("%d%s", low[i][j], (j == n ? "\n" : " "));
        for (int j = 0; j < n; j++)
            printf("%d%s", low[m][j], (j + 1 == n ? "\n" : " "));
    }
}

int main()
{
    sol();
}
