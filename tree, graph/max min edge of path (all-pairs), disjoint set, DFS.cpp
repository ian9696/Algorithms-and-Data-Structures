/*

max min edge of path (all-pairs), disjoint set, DFS

Introduction to Algorithms (Fall 2018)
Quiz 2.4 - Widest Paths
https://oj.nctu.edu.tw/problems/757/

*/

#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;

const int INF=0x3FFFFFFF;

struct DS
{
    vector<int> v;
    DS(int n):v(n, -1) {}
    int find(int x)
    {
        return v[x]==-1? x: (v[x]=find(v[x]));
    }
    bool join(int x, int y)
    {
        x=find(x);
        y=find(y);
        if(x==y)
            return false;
        v[x]=y;
        return true;
    }
};

struct Edge
{
    int u, v, w;
    Edge(int _u=-1, int _v=-1, int _w=-1): u(_u),v(_v),w(_w) {}
    bool operator<(const Edge &r) const
    {
        return w<r.w;
    }
};

void dfs(int s, int u, int p, vector<vector<Edge>> &E, vector<vector<int>> &D, int w)
{
    D[s][u]=w;
    for(Edge e: E[u])
        if(e.v!=p)
            dfs(s, e.v, u, E, D, min(w, e.w));
}

int main()
{
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);
    vector<Edge> F(m);
    for(int i=0; i<m; i++)
        scanf("%d%d%d", &F[i].u, &F[i].v, &F[i].w);
    sort(F.rbegin(), F.rend());
    DS ds(n);
    vector<vector<Edge>> E(n);
    for(Edge f: F)
    {
        if(!ds.join(f.u, f.v))
            continue;
        E[f.u].push_back(Edge(-1, f.v, f.w));
        E[f.v].push_back(Edge(-1, f.u, f.w));
    }
    vector<vector<int>> D(n, vector<int>(n, 0));
    for(int i=0; i<n; i++)
        dfs(i, i, -1, E, D, INF);
    for(int i=0; i<k; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        printf("%d\n", D[u][v]);
    }
}
