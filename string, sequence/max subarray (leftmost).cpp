/*

max subarray (leftmost)

Introduction to Algorithms (Fall 2018)
Quiz 1.3 - Maximum Subarray 2 (0 points, for practice only)
https://oj.nctu.edu.tw/problems/741/

*/

#include<cstdio>

typedef long long lld;

lld a[1000002];

int main()
{
    int n;
    scanf("%d", &n);
    for(int i=1; i<=n; i++)
        scanf("%lld", &a[i]);
    lld ans[3]= {a[n], n, n}, p[3]= {a[n], n, n};
    for(int i=n-1; i>=1; i--)
    {
        if(p[0]>0)
        {
            p[0]+=a[i];
            p[1]=i;
        }
        else
        {
            p[0]=a[i];
            p[1]=p[2]=i;
        }
        if(p[0]>=ans[0])
        {
            ans[0]=p[0];
            ans[1]=p[1];
            ans[2]=p[2];
        }
    }
    printf("%lld %lld\n", ans[1], ans[2]);
}
