/*

max weight independent set (MWIS), tree, DP, DFS, frank

Competitive Programming 1 (Spring 2018)
Assignment 17 (Week 13) - Maximum Weighted Independent Set
https://oj.nctu.edu.tw/problems/488/

written by frank

*/

#include<cstdio>
#include<vector>
using namespace std;
typedef long long lld;
const int N=1<<20;
vector<vector<int>> e(N);
vector<vector<lld>> a(N, vector<lld>(2, -1));
vector<lld> w(N);

lld solve(int k=1, int u=1, int p=-1)
{
    lld& ans=a[u][k];
    
    if( ans<0 )
    {
        ans= k ? w[u] : 0;
        
        for(int v : e[u])
            if( v!=p )
                ans+=solve(k^1, v, u);
        
        ans=max(ans, solve(0, u, p));
    }
    
    return ans;
}

void print(int k=1, int u=1, int p=-1)
{
    static bool init=true;
    
    if( k==1 && solve(1, u, p)==solve(0, u, p) )
    {
        print(0, u, p);
        return ;
    }
    
    if( k )
    {
        printf(init ? "%d" : " %d", u);
        init=false;
    }
    
    for(int v : e[u])
        if( v!=p )
            print(k^1, v, u);
}

int main()
{
    int n;
    scanf("%d", &n);
    
    for(int i=1; i<=n; i++)
        scanf("%lld", &w[i]);
    
    for(int i=1; i<n; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        e[u].push_back(v);
        e[v].push_back(u);
    }
    
    printf("%lld\n", solve());
    print();
    printf("\n");
}
