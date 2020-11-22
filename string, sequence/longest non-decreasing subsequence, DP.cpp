/*

longest non-decreasing subsequence, DP

Introduction to Algorithms (Fall 2017)
homework6.2 Longest Non-decreasing Subsequence
https://oj.nctu.edu.tw/problems/258/

*/

#include<cstdio>
#include<algorithm>
#include<vector>
#include<cstring>
using namespace std;

typedef long long lld;

int main()
{
    int T;
    for(scanf("%d", &T); T>0; T--)
    {
        int n;
        scanf("%d", &n);
        vector<int> dp(n, 1);
        vector<lld> a(n);
        for(int i=0; i<n; i++)
            scanf("%lld", &a[i]);
        int ans=0;
        for(int i=n-1; i>=0; i--)
        {
            for(int j=i+1; j<n; j++)
                if(a[i]<=a[j])
                    dp[i]=max(dp[i], 1+dp[j]);
            ans=max(ans, dp[i]);
        }
        printf("%d\n", ans);
    }
}
