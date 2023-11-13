/*

number of edges of each subgraph, Gray code, enumeration

Selected Topics in Intractable Problems (Spring 2019)
Sparsest Induced Graphs (Programming Assignment #2)
https://oj.nctu.edu.tw/problems/928/

*/

#include<cstdio>

const int N=30;

int main()
{
    int n, G[N], ans[N+1];
    scanf("%d", &n);
    for(int i=0; i<n; i++)
    {
        G[i]=0;
        for(int j=0; j<n; j++)
        {
            int t;
            scanf("%d", &t);
            G[i]|=t<<j;
        }
        ans[i+1]=n*n;
    }
    for(int b=0, g=0, ecnt=0; b<(1<<n)-1; )
    {
        b++;
        int p=b&(-b);
        g^=p;
        int bcnt=__builtin_popcount(g);
		ecnt+=__builtin_popcount(G[__builtin_ctz(p)]&g)*(g&p?1:-1);
		if(ecnt<ans[bcnt])
            ans[bcnt]=ecnt;
    }
    for(int i=2; i<=n; i++)
        printf("%d %d\n", i, ans[i]);
}