/*

min b s.t. lcm(a, b)=c, case analysis, prime factorization, sieve, GCD

Competitive Programming 1 (Spring 2018)
Assignment 10 (Week 8) - LCM
https://oj.nctu.edu.tw/problems/481/

*/

#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;

#define x first
#define y second
typedef long long lld;

bool P[100000];
vector<lld> p;

lld gcd(lld u, lld v)
{
    return v==0?u:gcd(v, u%v);
}

int main()
{
    for(int i=2; i<100000; i++)
        P[i]=1;
    for(lld i=2; i<100000; i++)
        if(P[i])
        {
            p.push_back(i);
            for(lld j=i*i; j<100000; j+=i)
                P[j]=0;
        }
    int T;
    for(scanf("%d", &T); T>0; T--)
    {
        lld a, c, a2, c2;
        scanf("%lld%lld", &a, &c);
        a2=a, c2=c;
        if(c%a)
        {
            printf("-1\n");
            continue;
        }
        lld ans=1;
        if(a<=1000000000)
        {
            vector<pair<lld, lld>> v;
            for(lld t: p)
            {
                if(a<=1)
                    break;
                if(a%t==0)
                {
                    v.push_back({t, 0});
                    while(a>1 && a%t==0)
                        v.back().y++, a/=t;
                }
            }
            if(a>1)
                v.push_back({a, 1});
            ans=c;
            for(auto pa: v)
            {
                lld cnt=0, tmp=1;
                while(c>1 && c%pa.x==0)
                    cnt++, c/=pa.x, tmp*=pa.x;
                if(cnt==pa.y)
                    ans/=tmp;
            }
        }
        else
        {
            a=c/a;
            vector<pair<lld, lld>> v;
            for(lld t: p)
            {
                if(a<=1)
                    break;
                if(a%t==0)
                {
                    v.push_back({t, 0});
                    while(a>1 && a%t==0)
                        v.back().y++, a/=t;
                }
            }
            if(a>1)
                v.push_back({a, 1});
            for(auto pa: v)
            {
                while(c>1 && c%pa.x==0)
                    ans*=pa.x, c/=pa.x;
            }
        }
        printf("%lld\n", ans);
    }
}
