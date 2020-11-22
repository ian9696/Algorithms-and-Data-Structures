/*

min cost circulation, out-of-kilter, Dijkstra

Combinatorial Optimization Algorithms
Minimum Cost Circulation
https://oj.nctu.edu.tw/problems/907/

*/

#include<iostream>
#include<vector>
#include<queue>
using namespace std;

typedef long long lld;
typedef pair<lld, int> li;

const lld INF = (1LL << 62) - 1;

struct out_of_kilter
{
    struct edge
    {
        int y, n;
        lld u, c;
        edge(int _y, int _n, lld _u, lld _c) :y(_y), n(_n), u(_u), c(_c) {}
    };

    int n, en;
    lld cost;
    vector<edge> e;
    vector<int> head, pa, pai;
    vector<lld> pt;

    out_of_kilter(int _n) : n(_n), en(0), cost(0), head(_n, -1), pt(_n, 0) {}

    void add_edge(int x, int y, lld u, lld c)
    {
        e.push_back(edge(y, head[x], u, c)), head[x] = en++;
        e.push_back(edge(x, head[y], 0, -c)), head[y] = en++;
    }

    bool is_in_Kilter(int i)
    {
        int x = e[i ^ 1].y, y = e[i].y;
        lld c = e[i].c - pt[x] + pt[y];
        if (e[i].u == 0)
            return c <= 0;
        else if (e[i ^ 1].u == 0)
            return c >= 0;
        else
            return c == 0;
    }

    void augment(int x, int y, lld& f)
    {
        if (x == y)
            return;
        f = min(f, e[pai[y]].u);
        augment(x, pa[y], f);
        e[pai[y]].u -= f;
        e[pai[y] ^ 1].u += f;
        cost += f * e[pai[y]].c;
    }

    lld operator()()
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < en; j++)
                if (!is_in_Kilter(j))
                {
                    int x = e[j ^ 1].y, y = e[j].y;
                    priority_queue<li> pq;
                    vector<lld> d(n, INF);
                    vector<bool> vis(n, 0);
                    pa.assign(n, -1);
                    pai.assign(n, -1);
                    pq.push(li(d[y] = 0, y));
                    while (!pq.empty())
                    {
                        int a = pq.top().second;
                        lld c = -pq.top().first;
                        pq.pop();
                        if (vis[a])
                            continue;
                        vis[a] = 1;
                        for (int k = head[a]; k != -1; k = e[k].n)
                        {
                            int b = e[k].y;
                            lld u = e[k].u, c = max(0LL, e[k].c - pt[a] + pt[b]);
                            if (vis[b] || u <= 0)
                                continue;
                            if (d[b] > d[a] + c)
                            {
                                d[b] = d[a] + c;
                                pa[b] = a;
                                pai[b] = k;
                                pq.push(li(-d[b], b));
                            }
                        }
                    }
                    if (!vis[x])
                        continue;
                    if (e[j].c - pt[x] + pt[y] < 0)
                    {
                        lld f = e[j].u;
                        augment(y, x, f);
                        e[j].u -= f;
                        e[j ^ 1].u += f;
                        cost += f * e[j].c;
                    }
                    for (int k = 0; k < n; k++)
                        pt[k] -= vis[k] ? d[k] : d[x];
                }
        }
        return cost;
    }
};

int main()
{
    int n, m, x, y;
    lld u, c;
    cin >> n >> m;
    out_of_kilter OOK(n);
    while (m--)
    {
        cin >> x >> y >> u >> c;
        OOK.add_edge(x - 1, y - 1, u, c);
    }
    cout << OOK() << endl;
}
