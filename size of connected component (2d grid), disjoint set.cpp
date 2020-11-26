/*

size of connected component (2d grid), disjoint set

Introduction to Algorithms (Fall 2018)
Quiz 2.7 - Painting
https://oj.nctu.edu.tw/problems/760/

*/

#include<cstdio>
#include<algorithm>
#include<vector>
#include<string>
using namespace std;

#define x first
#define y second

struct Query
{
    int t, x, y;
};

struct Node
{
    int x, y, siz;
    Node(int _x=0, int _y=0, int _siz=0):x(_x),y(_y),siz(_siz) {}
};

struct DS
{
    int n, m;
    vector<vector<Node>> v;
    DS(int _n, int _m):n(_n),m(_m)
    {
        v.assign(n+1, vector<Node>(m+1));
        for(int i=1; i<=n; i++)
            for(int j=1; j<=m; j++)
            {
                v[i][j].x=i, v[i][j].y=j;
                v[i][j].siz=1;
            }
    }
    Node find(Node p)
    {
        return v[p.x][p.y].x==p.x&&v[p.x][p.y].y==p.y?p:v[p.x][p.y]=find(v[p.x][p.y]);
    }
    void join(Node l, Node r)
    {
        l=find(l), r=find(r);
        if(l.x==r.x && l.y==r.y)
            return;
        v[l.x][l.y].siz+=v[r.x][r.y].siz;
        v[r.x][r.y]=l;
    }
};

int main()
{
    int n, m, q;
    scanf("%d%d%d", &n, &m, &q);
    vector<Query> Q(q);
    for(int i=0; i<q; i++)
    {
        char s[10];
        scanf("%s%d%d", s, &Q[i].x, &Q[i].y);
        Q[i].t=s[0]=='p'?1:2;
    }
    vector<vector<bool>> B(n+2, vector<bool>(m+2, false));
    DS ds(n, m);
    for(int i=0; i<q; i++)
    {
        if(Q[i].t==1)
        {
            if(B[Q[i].x][Q[i].y])
                Q[i].t=0;
            else
            {
                B[Q[i].x][Q[i].y]=true;
                for(int k=-1; k<=1; k++)
                    for(int l=-1; l<=1; l++)
                        if(abs(k)+abs(l)==1 && B[Q[i].x+k][Q[i].y+l])
                            ds.join(Node(Q[i].x, Q[i].y), Node(Q[i].x+k, Q[i].y+l));
            }
        }
        else if(Q[i].t==2 && B[Q[i].x][Q[i].y])
        {
            auto p=ds.find(Node(Q[i].x, Q[i].y));
            Q[i].t=-ds.v[p.x][p.y].siz;
        }
    }
    for(int i=0; i<n+2; i++)
        B[i][0]=B[i][m+1]=true;
    for(int j=0; j<m+2; j++)
        B[0][j]=B[n+1][j]=true;
    ds=DS(n, m);
    for(int i=1; i<=n; i++)
        for(int j=1; j<=m; j++)
            for(int k=-1; k<=1; k++)
                for(int l=-1; l<=1; l++)
                    if(abs(k)+abs(l)==1 && !B[i][j] && !B[i+k][j+l])
                        ds.join(Node(i, j), Node(i+k, j+l));
    for(int i=q-1; i>=0; i--)
    {
        if(Q[i].t==1)
        {
            B[Q[i].x][Q[i].y]=false;
            for(int k=-1; k<=1; k++)
                for(int l=-1; l<=1; l++)
                    if(abs(k)+abs(l)==1 && !B[Q[i].x+k][Q[i].y+l])
                        ds.join(Node(Q[i].x, Q[i].y), Node(Q[i].x+k, Q[i].y+l));
        }
        else if(Q[i].t==2)
        {
            auto p=ds.find(Node(Q[i].x, Q[i].y));
            Q[i].t=-ds.v[p.x][p.y].siz;
        }
    }
    for(int i=0; i<q; i++)
        if(Q[i].t<0)
            printf("%d\n", -Q[i].t);
}
