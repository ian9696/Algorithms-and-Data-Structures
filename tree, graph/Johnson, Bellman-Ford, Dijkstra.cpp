/*

Johnson, Bellman-Ford, Dijkstra

Introduction to Algorithms (Fall 2017)
homework11.1 Johnson’s algorithm
https://oj.nctu.edu.tw/problems/333/

*/

#include<cstdio>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;

typedef long long lld;

const lld INF=0x3FFFFFFFFFFFFFFF;

int main()
{
    int n, m, q;
    scanf("%d%d%d", &n, &m, &q);
    vector<vector<pair<int, lld>>> E(n+1);
    for(int i=0; i<m; i++)
    {
        int u, v;
        lld w;
        scanf("%d%d%lld", &u, &v, &w);
        E[u].push_back({v, w});
    }
    for(int i=1; i<=n; i++)
        E[0].push_back({i, 0});
    vector<lld> d(n+1, INF);
    d[0]=0;
    for(int k=1; k<=n+1; k++)
        for(int i=0; i<=n; i++)
            for(auto &pa: E[i])
                if(d[i]<INF)
                    d[pa.first]=min(d[pa.first], d[i]+pa.second);
    for(int i=1; i<=n; i++)
        for(auto &pa: E[i])
            pa.second+=d[i]-d[pa.first];
    vector<vector<lld>> dp(n+1, vector<lld>(n+1, INF));
    for(int s=1; s<=n; s++)
    {
        vector<int> used(n+1);
        priority_queue<pair<lld, int>, vector<pair<lld, int>>, greater<pair<lld, int>>> pq;
        pq.push({0, s});
        while(!pq.empty())
        {
            auto pa=pq.top();
            pq.pop();
            int u=pa.second;
            if(used[u])
                continue;
            used[u]=1;
            dp[s][u]=pa.first;
            for(auto &e: E[u])
            {
                int v=e.first;
                lld w=e.second;
                if(!used[v] && dp[s][u]+w<dp[s][v])
                {
                    dp[s][v]=dp[s][u]+w;
                    pq.push({dp[s][v], v});
                }
            }
        }
    }
    for(; q>0; q--)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        if(dp[u][v]<INF)
            printf("%lld\n", dp[u][v]-d[u]+d[v]);
        else
            printf("no path\n");
    }
}
