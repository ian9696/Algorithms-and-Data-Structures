/*

tree diameter, BFS

Introduction to Algorithms (Fall 2018)
Assignment 17 - Tree Diameter (0 points, for practice only)
https://oj.nctu.edu.tw/problems/715/

*/

#include<cstdio>
#include<vector>
#include<queue>
using namespace std;

int n;
vector<vector<int>> E;

pair<int, int> bfs(int s)
{
    queue<int> Q;
    vector<int> d(n, -1);
    d[s]=0;
    for(Q.push(s); !Q.empty(); Q.pop())
    {
        s=Q.front();
        for(int v: E[s])
            if(d[v]==-1)
            {
                d[v]=d[s]+1;
                Q.push(v);
            }
    }
    return {s, d[s]};
}

int main()
{
    scanf("%d", &n);
    E.resize(n);
    for(int i=0; i<n-1; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        E[u].push_back(v);
        E[v].push_back(u);
    }
    auto pa=bfs(0);
    printf("%d\n", bfs(pa.first).second);
}
