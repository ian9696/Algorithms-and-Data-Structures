/*

size of connected component (2d grid), union by size heuristic

Introduction to Algorithms (Fall 2018)
Quiz 2.7 - Painting
https://oj.nctu.edu.tw/problems/760/

*/

#include<cstdio>
#include<algorithm>
#include<vector>
#include<set>
using namespace std;

struct Query
{
    int t, x, y;
};

int n, m, q, to[4][2]= {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
vector<vector<int>> L, M;

int I(int x, int y)
{
    return x*m+y;
}

bool R(int x, int y)
{
    return x>=0 && x<n && y>=0 && y<m;
}

void C(int x, int y, int u, int v)
{
    if(M[L[x][y]].size()<M[L[u][v]].size())
    {
        swap(x, u);
        swap(y, v);
    }
    u=L[u][v];
    for(int t: M[u])
    {
        int a=t/m, b=t%m;
        L[a][b]=L[x][y];
        M[L[x][y]].push_back(t);
    }
    M[u].clear();
}

int main()
{
    scanf("%d%d%d", &n, &m, &q);
    set<pair<int, int>> S;
    vector<Query> Q;
    for(; q>0; q--)
    {
        Query t;
        char s[100];
        scanf("%s%d%d", s, &t.x, &t.y);
        t.x--, t.y--;
        t.t=(s[0]=='r'?2:1);
        if(t.t==1 && !S.insert({t.x, t.y}).second)
            continue;
        Q.push_back(t);
    }
    L.assign(n, vector<int>(m, -1));
    M.assign(n*m, vector<int>());
    for(int k=0; k<=1; k++)
    {
        for(Query &t: Q)
        {
            if(t.t==1)
            {
                L[t.x][t.y]=I(t.x, t.y);
                M[I(t.x, t.y)]= {I(t.x, t.y)};
                for(int l=0; l<4; l++)
                {
                    int u=t.x+to[l][0], v=t.y+to[l][1];
                    if(R(u, v) && L[u][v]!=-1 && L[u][v]!=L[t.x][t.y])
                        C(t.x, t.y, u, v);
                }
            }
            else if(t.t==2 && L[t.x][t.y]!=-1)
                t.t=(int)M[L[t.x][t.y]].size()*-1;
        }
        for(int i=0; i<n; i++)
            for(int j=0; j<m; j++)
            {
                if(L[i][j]!=-1)
                {
                    L[i][j]=-1;
                    M[I(i, j)].clear();
                }
                else
                {
                    L[i][j]=I(i, j);
                    M[I(i, j)]= {I(i, j)};
                }
            }
        for(int i=0; i<n; i++)
            for(int j=0; j<m; j++)
                for(int l=0; l<4; l++)
                {
                    int u=i+to[l][0], v=j+to[l][1];
                    if(R(u, v) && min(L[i][j], L[u][v])>-1 && L[u][v]!=L[i][j])
                        C(i, j, u, v);
                }
        reverse(Q.begin(), Q.end());
    }
    for(Query &t: Q)
        if(t.t<=0)
            printf("%d\n", -t.t);
}
