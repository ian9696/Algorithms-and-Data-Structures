/*

number of Hamiltonian cycles (directed graph), inclusion-exclusion principle (n-walk starts from any vertex), enumeration, Floyd-Warshall, DP

Selected Topics in Intractable Problems (Spring 2019)
Principle of Inclusion and Exclusion (Programming Assignment #4)
https://oj.nctu.edu.tw/problems/930/

*/

#include<cstdio>
#include<vector>
using namespace std;

typedef long long lld;

const int N=17;
lld G[N][N], Gt[N][N], A[2][N][N];

lld cal(int nt, int n)
{
    for(int i=0; i<nt; i++)
        for(int j=0; j<nt; j++)
            A[0][i][j]=Gt[i][j];
    int t=1, s=0;
    for(; t<n; t++, s^=1)
    {
        for(int i=0; i<nt; i++)
            for(int j=0; j<nt; j++)
            {
                A[s^1][i][j]=0;
                for(int k=0; k<nt; k++)
                    A[s^1][i][j]+=A[s][i][k]*Gt[k][j];
            }
    }
    lld res=0;
    for(int i=0; i<nt; i++)
        res+=A[s][i][i];
    return res;
}

int main()
{
    int n;
    scanf("%d", &n);
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            scanf("%d", &G[i][j]);
    lld ans=0;
    for(int b=1; b<1<<n; b++)
    {
        vector<int> rem;
        for(int i=0; i<n; i++)
            if(b>>i&1)
                rem.push_back(i);
        for(int i=0; i<rem.size(); i++)
            for(int j=0; j<rem.size(); j++)
                Gt[i][j]=G[rem[i]][rem[j]];
        ans+=cal(rem.size(), n)*(n-rem.size()&1?-1:1);
    }
    ans/=n;
    printf("%lld\n", ans);
}