/*

edges in at least 1 MST, Kruskal's algorithm, minimum spanning tree (MST), disjoint set

Introduction to Algorithms (Fall 2017)
homework10.1 Edges in MST
https://oj.nctu.edu.tw/problems/303/

*/

#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;

const int N=100001;
int a[N+1];

int get(int x)
{
    return a[x]==0?x:a[x]=get(a[x]);
}

void join(int x, int y)
{
    x=get(x);
    y=get(y);
    if(x!=y)
        a[x]=y;
}

int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    vector<vector<int>> E(m);
    for(int i=0; i<m; i++)
    {
        E[i].assign(4, i);
        scanf("%d%d%d", &E[i][1], &E[i][2], &E[i][0]);
    }
    sort(E.begin(), E.end());
    vector<bool> ans(m);
    for(int i=0, j=0; i<m; i++)
    {
        while(E[j][0]<E[i][0])
            join(E[j][1], E[j][2]), j++;
        if(get(E[i][1])!=get(E[i][2]))
            ans[E[i][3]]=true;
    }
    for(int i=0; i<m; i++)
        printf("%s\n", ans[i]?"at least one":"none");
}
