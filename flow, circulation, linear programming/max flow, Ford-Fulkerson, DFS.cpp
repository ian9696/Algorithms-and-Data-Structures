/*

max flow, Ford-Fulkerson, DFS

Introduction to Algorithms (Fall 2017)
homework11.2 Dining
https://oj.nctu.edu.tw/problems/334/

*/

#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;

const int INF=0x3FFFFFFF;

struct FF
{
    struct Edge
    {
        int v, c, r;
        Edge(int _v, int _c, int _r):v(_v),c(_c),r(_r) {}
    };
    int n;
    vector<vector<Edge>> E;
    vector<int> used;
    FF(int _n):n(_n),E(_n),used(_n) {}
    void add(int u, int v, int c)
    {
        E[u].push_back(Edge(v, c, E[v].size()));
        E[v].push_back(Edge(u, 0, E[u].size()-1));
    }
    int dfs(int s, int t, int num)
    {
        used[s]=1;
        if(s==t)
            return num;
        for(Edge &e: E[s])
        {
            if(e.c>0 && !used[e.v])
            {
                int tmp=dfs(e.v, t, min(num, e.c));
                if(tmp>0)
                {
                    e.c-=tmp;
                    E[e.v][e.r].c+=tmp;
                    return tmp;
                }
            }
        }
        return 0;
    }
    int operator()(int s, int t)
    {
        int res=0, tmp=0;
        while(tmp=dfs(s, t, INF))
        {
            res+=tmp;
            used.assign(n, 0);
        }
        return res;
    }
};

int main()
{
    int T;
    for(scanf("%d", &T); T>0; T--)
    {
        int n, m;
        scanf("%d%d", &n, &m);
        int N=n+m+2, sum=0;
        FF F(N);
        for(int i=0; i<n; i++)
        {
            int t;
            scanf("%d", &t);
            F.add(N-2, i, t);
            sum+=t;
        }
        for(int i=0; i<m; i++)
        {
            int t;
            scanf("%d", &t);
            F.add(n+i, N-1, t);
        }
        for(int i=0; i<n; i++)
            for(int j=0; j<m; j++)
                F.add(i, n+j, 1);
        printf("%s\n", (F(N-2, N-1)==sum?"Yes":"No"));
    }
}
