/*

min vertex cover, tree, Hopcroft-Karp

Introduction to Algorithms (Fall 2017)
Quiz2-2. Guard(Practice)
https://oj.nctu.edu.tw/problems/361/

*/

#include<cstdio>
#include<cstdlib>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;
const int INF=1<<20;

struct HK
{
    int n;
    vector<vector<int>> e, f;
    vector<bool> vis;
    vector<int> d, p;
    queue<int> Q;
    HK(int _n) : n(_n), f(n+1){}
    
    void add(int u, int v)
    {
        f[u].push_back(v);
        f[v].push_back(u);
    }
    
    void bfs()
    {
        e.clear();
        e.resize(n+1);
        d.assign(n+1, 0);
        p.assign(n+1, 0);
        vis.assign(n+1, false);
        vector<int> o;
        
        for(int i=1; i<=n; i++)
            o.push_back(i);
        
        random_shuffle(o.begin(), o.end());
        
        for(int i=1; i<=n; i++)
            random_shuffle(f[i].begin(), f[i].end());
        
        for(int u : o)
        {
            if( vis[u] )
                continue;
            
            vis[u]=true;
            
            for(Q.push(u); !Q.empty(); Q.pop())
            {
                u=Q.front();
                
                for(int v : f[u])
                    if( !vis[v] )
                    {
                        vis[v]=true;
                        Q.push(v);
                        d[u]++;
                        p[v]=u;
                    }
            }
        }
    }
    
    int operator()()
    {
        bfs();
        vis.assign(n+1, false);
        int tmp=0;
        
        for(int i=1; i<=n; i++)
            if( d[i]==0 )
                Q.push(i);
        
        for(; !Q.empty(); Q.pop())
        {
            int u=Q.front();
            int v=p[u];
            
            if( vis[u] )
                tmp++;
            else if( v!=0 )
                vis[v]=true;
        
            if( --d[v]==0 )
                Q.push(v);
        }
        
        return tmp;
    }
};

int main()
{
    int n;
    scanf("%d", &n);
    HK hk(n);
    
    for(int i=1; i<n; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        hk.add(u, v);
    }
    
    printf("%d\n", hk());
}
