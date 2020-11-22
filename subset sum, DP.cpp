/*

subset sum, DP

Introduction to Algorithms (Fall 2017)
homework8.2 Maximum Xor
https://oj.nctu.edu.tw/problems/288/

*/

#include<cstdio>
#include<vector>
#include<cstring>
using namespace std;

const int N=1<<10;
const int M=3;

int main()
{
    int T;
    for(scanf("%d", &T); T>0; T--)
    {
        int n;
        scanf("%d", &n);
        vector<bool> dp(N);
        dp[0]=1;
        for(int i=0; i<n; i++)
        {
            vector<bool> tmp(N);
            for(int j=0; j<M; j++)
            {
                int t;
                scanf("%d", &t);
                for(int k=0; k<N; k++)
                    if(dp[k])
                        tmp[k^t]=true;
            }
            dp.swap(tmp);
        }
        for(int i=N-1; i>=0; i--)
            if(dp[i])
            {
                printf("%d", i);
                break;
            }
        if(T>1)
            printf("\n");
    }
}
