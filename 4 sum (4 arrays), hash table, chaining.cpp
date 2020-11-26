/*

4 sum (4 arrays), hash table, chaining

Introduction to Algorithms (Fall 2018)
Assignment 9 - Counting Tuples (Deadline: 10/27 23:59:59)
https://oj.nctu.edu.tw/problems/666/

*/

#include<cstdio>
#include<vector>
using namespace std;

typedef long long lld;

const lld X=1000003;
vector<pair<lld, lld>> cnt[X];

lld H(lld x)
{
    return (x%X+X)%X;
}

int main()
{
    lld n, x;
    vector<lld> v[2];
    scanf("%lld%lld", &n, &x);
    for(int i=0; i<2; i++)
    {
        v[i].resize(n);
        for(int j=0; j<n; j++)
            scanf("%lld", &v[i][j]);
    }
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
        {
            lld val=v[0][i]+v[1][j];
            lld h=H(val);
            bool has=false;
            for(auto &pa: cnt[h])
                if(pa.first==val)
                {
                    has=true;
                    pa.second++;
                }
            if(!has)
                cnt[h].push_back(pair<lld, lld>(val, 1));
        }
    for(int i=0; i<2; i++)
    {
        v[i].resize(n);
        for(int j=0; j<n; j++)
            scanf("%lld", &v[i][j]);
    }
    lld ans=0;
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
        {
            lld val=x-v[0][i]-v[1][j];
            lld h=H(val);
            for(auto &pa: cnt[h])
                if(pa.first==val)
                {
                    ans+=pa.second;
                    break;
                }
        }
    printf("%lld\n", ans);
}
