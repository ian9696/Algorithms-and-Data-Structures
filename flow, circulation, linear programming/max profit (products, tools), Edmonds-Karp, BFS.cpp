/*

max profit (products, tools), Edmonds-Karp, BFS

Introduction to Algorithms (Fall 2018)
Quiz 2.6 - Maximum Profit
https://oj.nctu.edu.tw/problems/759/

*/

#include<cstdio>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;

typedef long long lld;

const lld INF=(1LL<<62)-1;

struct EK
{
    int n;
    vector<vector<lld>> E;
    EK(int _n): n(_n), E(_n, vector<lld>(_n, 0)) {}
    lld operator()(int s, int t)
    {
        lld ans=0;
        while(1)
        {
            vector<int> pre(n, -1);
            queue<int> Q;
            pre[s]=s;
            for(Q.push(s); !Q.empty(); Q.pop())
            {
                int u=Q.front();
                for(int v=0; v<n; v++)
                    if(E[u][v]>0 && pre[v]==-1)
                    {
                        pre[v]=u;
                        Q.push(v);
                    }
            }
            if(pre[t]==-1)
                break;
            lld mine=INF;
            for(int u=pre[t], v=t; v!=s; v=u, u=pre[u])
                mine=min(mine, E[u][v]);
            for(int u=pre[t], v=t; v!=s; v=u, u=pre[u])
            {
                E[u][v]-=mine;
                E[v][u]+=mine;
            }
            ans+=mine;
        }
        return ans;
    }
};

int main()
{
    int n, m, c;
    scanf("%d%d%d", &n, &m, &c);
    EK ek(n+m+2);
    lld sum=0;
    for(int i=0; i<n+m; i++)
    {
        lld w;
        scanf("%lld", &w);
        if(i<n)
            w=-w;
        if(w>=0)
        {
            ek.E[n+m][i]=w;
            sum+=w;
        }
        else
            ek.E[i][n+m+1]=-w;
    }
    for(int i=0; i<c; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        u--, v--;
        ek.E[n+u][v]=INF;
    }
    printf("%lld\n", sum-ek(n+m, n+m+1));
}
