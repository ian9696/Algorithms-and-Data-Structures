/*

detect odd cycle (undirected graph, edge insertion), disjoint set (xor path to root)

Codeforces Round #360 (Div. 1)
D. Dividing Kingdom II
https://codeforces.com/contest/687/problem/D

path compression of disjoint set is modified
find function takes more time
need less space

*/

#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;

#define x first
#define y second

struct Edge
{
    int u, v, w, id;
    bool operator<(const Edge& r) const
    {
        return w > r.w;
    }
};

int a[1001];
Edge e[1000000];
int n, m, q;

pair<int, int> find(int x)
{
    if (!a[x])
        return { x, 0 };
    auto y = find(a[x]);
    y.y ^= 1;
    if (y.y)
        a[x] = y.x;
    return y;
}
bool query(int l, int r)
{
    auto x = find(l);
    auto y = find(r);
    if (x.x == y.x)
        return x.y == y.y;
    if (x.y == y.y)
        a[x.x] = y.x;
    else
        x.y ? a[y.x] = l : a[x.x] = r;
    return 0;
}
void clear()
{
    for (int i = 1; i <= n; i++)
        a[i] = 0;
}

int main()
{
    scanf("%d%d%d", &n, &m, &q);
    for (int i = 0; i < m; i++)
        scanf("%d%d%d", &e[i].u, &e[i].v, &e[i].w), e[i].id = i;
    sort(e, e + m);
    for (int i = 0, l, r, p; i < q; i++)
    {
        clear();
        scanf("%d%d", &l, &r);
        l--, r--;
        for (p = 0; p < m; p++)
            if (l <= e[p].id && e[p].id <= r && query(e[p].u, e[p].v))
                break;
        printf("%d\n", p == m ? -1 : e[p].w);
    }
}
