/*

min cost circulation, successive shortest path, Dijkstra, BFS

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

struct successive_shortest_path
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
    vector<lld> ex;
    vector<bool> vis;

    successive_shortest_path(int _n) : n(_n), en(0), cost(0), head(_n, -1), ex(_n, 0) {}

    void add_edge(int x, int y, lld u, lld c)
    {
        e.push_back(edge(y, head[x], u, c)), head[x] = en++;
        e.push_back(edge(x, head[y], 0, -c)), head[y] = en++;
    }

    void saturate()
    {
        for (int i = 0; i < en; i += 2)
            if (e[i].c < 0)
            {
                cost += e[i].u * e[i].c;
                ex[e[i].y] += e[i].u;
                ex[e[i + 1].y] -= e[i].u;
                e[i + 1].u = e[i].u;
                e[i].u = 0;
            }
    }

    int bfs(int x)
    {
        queue<int> q;
        q.push(x);
        vis[x] = 1;
        while (!q.empty())
        {
            int a = q.front();
            q.pop();
            if (ex[a] < 0)
                return a;
            for (int i = head[a]; i != -1; i = e[i].n)
            {
                int b = e[i].y, c = e[i].u;
                if (!vis[b] && c > 0)
                {
                    q.push(b);
                    vis[b] = 1;
                };
            }
        }
        return -1;
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
        vector<lld> pt(n, 0);
        saturate();
        while (1)
        {
            int x = 0, y = -1;
            vis.assign(n, 0);
            for (; x < n; x++)
                if (!vis[x] && ex[x] > 0 && (y = bfs(x)) != -1)
                    break;
            if (y == -1)
                break;
            priority_queue<li> pq;
            vector<lld> d(n, INF);
            vis.assign(n, 0);
            pa.assign(n, -1);
            pai.assign(n, -1);
            pq.push(li(d[x] = 0, x));
            while (!pq.empty())
            {
                int a = pq.top().second;
                lld c = -pq.top().first;
                pq.pop();
                if (vis[a])
                    continue;
                vis[a] = 1;
                for (int i = head[a]; i != -1; i = e[i].n)
                {
                    int b = e[i].y;
                    lld u = e[i].u, c = e[i].c - pt[a] + pt[b];
                    if (vis[b] || u <= 0)
                        continue;
                    if (d[b] > d[a] + c)
                    {
                        d[b] = d[a] + c;
                        pa[b] = a;
                        pai[b] = i;
                        pq.push(li(-d[b], b));
                    }
                }
            }
            lld f = min(ex[x], -ex[y]);
            augment(x, y, f);
            ex[x] -= f;
            ex[y] += f;
            for (int i = 0; i < n; ++i)
                pt[i] -= vis[i] ? d[i] : d[y];
        }
        return cost;
    }
};

int main()
{
    int n, m, x, y;
    lld u, c;
    cin >> n >> m;
    successive_shortest_path SSP(n);
    while (m--)
    {
        cin >> x >> y >> u >> c;
        SSP.add_edge(x - 1, y - 1, u, c);
    }
    cout << SSP() << endl;
}
