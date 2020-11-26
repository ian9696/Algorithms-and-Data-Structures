/*

highest tower (weight, endurance), DP

Introduction to Algorithms (Fall 2018)
Assignment 13 - Box Tower (Deadline: 11/10 23:59:59)
https://oj.nctu.edu.tw/problems/675/

*/

#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;

const int INF=0x3FFFFFFF;

#define w second
#define d first

int main()
{
    int n;
    scanf("%d", &n);
    vector<pair<int, int>> v(n);
    for(int i=0; i<n; i++)
        scanf("%d%d", &v[i].w, &v[i].d);
    sort(v.begin(), v.end());
    vector<int> dp(n+1, INF);
    dp[0]=0;
    for(int i=0; i<n; i++)
        for(int j=n; j>=1; j--)
            if(dp[j-1]+v[i].w<=v[i].d)
                dp[j]=min(dp[j], dp[j-1]+v[i].w);
    for(int i=n; i>=0; i--)
        if(dp[i]!=INF)
        {
            printf("%d\n", i);
            break;
        }
}
