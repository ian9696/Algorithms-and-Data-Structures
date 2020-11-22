/*

disjoint set

Introduction to Algorithms (Fall 2017)
homework9.1 朋友的朋友
https://oj.nctu.edu.tw/problems/289/

*/

#include<bits/stdc++.h>
using namespace std;

const int N=30000;
int a[N+1], cnt[N+1], ans;

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
    for(; m>0; m--)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        join(u, v);
    }
    for(int i=1; i<=n; i++)
        ans=max(ans, ++cnt[get(i)]);
    printf("%d", ans);
}
