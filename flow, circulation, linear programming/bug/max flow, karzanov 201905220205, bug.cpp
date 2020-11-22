/*

max flow, karzanov 201905220205, bug

*/

#include<cstdio>
#include<algorithm>
#include<vector>
#include<queue>
#include<cstring>
using namespace std;

const int INF = 0x3FFFFFFF;

struct Karzanov
{
    struct edge
    {
        int t, c, r;
        edge(int _t, int _c, int _r) : t(_t), c(_c), r(_r) {}
    };
    vector<int> l, L;
    vector<vector<edge>> e;
    vector<int> ex;
    vector<vector<vector<int>>> st;
    Karzanov(int n) : e(n + 1), ex(n + 1), st(n + 1) {}
    int ans2, s2, t2;
    void add(int u, int v, int w)
    {
        e[u].push_back(edge(v, w, e[v].size()));
        e[v].push_back(edge(u, 0, e[u].size() - 1));
    }
    edge& rev(const edge& E)
    {
        return e[E.t][E.r];
    }
    bool bfs(int s, int t)
    {
        l.assign(e.size(), INF);
        l[s] = 1;
        queue<int> Q;
        for (Q.push(s); !Q.empty(); Q.pop())
        {
            s = Q.front();
            L.push_back(s);
            for (const edge& E : e[s])
                if (E.c > 0 && l[E.t] > l[s] + 1)
                {
                    l[E.t] = l[s] + 1;
                    Q.push(E.t);
                }
        }
        return l[t] < INF;
    }
    void ch(int u, int p, int val)
    {
        int v = e[u][p].t, r = e[u][p].r;
        e[u][p].c -= val;
        e[v][r].c += val;
        ex[u] -= val;
        ex[v] += val;
        if(u==t2)
            ans2-=val;
        else if(v==t2)
            ans2+=val;
    }
    void push(int u, int p, int val)
    {
        if (!val)
            return;
        int v = e[u][p].t, r = e[u][p].r;
        ch(u, p, val);
        st[v].push_back({ u, p, val });
    }
    int operator()(int s, int t)
    {
        int ans = 0;
        ans2=0, s2=s, t2=t;
        for (; bfs(s, t); )
        {
            vector<bool> dead(l.size()), in(l.size());
            while (L.back() != t)
                L.pop_back();
            L.pop_back();
            reverse(L.begin(), L.end());
            L.pop_back();
            reverse(L.begin(), L.end());
            for (int u : L)
                in[u] = 1;
            in[s] = in[t] = 1;

            for (int i = 0; i < e[s].size(); i++)
            {
                int val=e[s][i].c;
                push(s, i, val);
            }
            while (1)
            {
                for (int u : L)
                {
                    if (dead[u] || ex[u] <= 0)
                        continue;
                    for (int i = 0; i < e[u].size() && ex[u]>0; i++)
                    {
                        edge& E = e[u][i];
                        if (E.c > 0 && l[u] + 1 == l[E.t] && !dead[E.t] && in[E.t])
                        {
                            int val = min(ex[u], E.c);
                            push(u, i, val);
                        }
                    }
                }
                int u = -1;
                for (auto it = L.rbegin(); it != L.rend(); it++)
                    if (!dead[*it] && ex[*it] > 0)
                    {
                        u = *it;
                        break;
                    }
                if (u == -1)
                    break;
                while (ex[u] > 0)
                {
                    int v = st[u].back()[0], p = st[u].back()[1];
                    int val = min(ex[u], st[u].back()[2]);
                    ch(v, p, -val);
                    st[u].back()[2] -= val;
                    if (st[u].back()[2] == 0)
                        st[u].pop_back();
                }
                dead[u] = 1;
            }
            L.clear();
            ex.assign(l.size(), 0);
            st.assign(l.size(), vector<vector<int>>());
        }
        return ans2;
    }
};

int main()
{
    freopen("12829.input", "r", stdin);
    int n, m;
    scanf("%d %d", &n, &m);

    Karzanov D(n);
    int S = 0, T = n-1;

    for (int i = 1; i <= m; i++)
    {
        int x, y, u;
        scanf("%d %d %d", &x, &y, &u);
        x--, y--;
        D.add(x, y, u);
    }
    int sum=0, sum2=0;
    for(const Karzanov::edge &E: D.e[S])
        sum+=E.c;

    printf("%d\n", D(S, T));

    for(const Karzanov::edge &E: D.e[S])
        sum2+=E.c;
        printf("sum=%d sum2=%d\n", sum, sum2);

    for(int i=0; i<n; i++)
        if(D.ex[i]!=0)
            printf("~~~ %d %d\n", i, D.ex[i]);
}
