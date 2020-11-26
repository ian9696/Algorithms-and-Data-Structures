/*

4 sum (4 array, increasing index), unordered_map

Introduction to Algorithms (Fall 2018)
Quiz 1.5 - Counting Tuples 2 (0 points, for practice only)
https://oj.nctu.edu.tw/problems/743/

*/

#include<cstdio>
#include<vector>
#include<unordered_map>
using namespace std;

typedef long long lld;

int main()
{
    int n;
    lld x;
    scanf("%d%lld", &n, &x);
    vector<lld> v[4];
    for(int i=0; i<4; i++)
    {
        v[i].resize(n);
        for(int j=0; j<n; j++)
            scanf("%lld", &v[i][j]);
    }
    unordered_map<lld, lld> M;
    lld ans=0;
    for(int j=n-1; j>=0; j--)
    {
        for(int l=j+2; l<n; l++)
            M[v[2][j+1]+v[3][l]]++;
        for(int i=j-1; i>=0; i--)
        {
            lld tmp=x-v[0][i]-v[1][j];
            if(M.find(tmp)!=M.end())
                ans+=M[tmp];
        }
    }
    printf("%lld\n", ans);
}
