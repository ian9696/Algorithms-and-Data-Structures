/*

min b s.t. lcm(a, b)=c, LCM, GCD, frank

Competitive Programming 1 (Spring 2018)
Assignment 10 (Week 8) - LCM
https://oj.nctu.edu.tw/problems/481/

written by frank

*/

#include<cstdio>
typedef long long lld;

lld gcd(lld a, lld b)
{
    return b==0 ? a : gcd(b, a%b);
}

lld lcm(lld a, lld b)
{
    return a/gcd(a, b)*b;
}

lld solve(lld a, lld c)
{
    if( c%a )
        return -1;
    
    for(lld b=1; ; )
    {
        if( lcm(a, b)==c )
            return b;
        
        b*=c/lcm(a, b);
    }
}

int main()
{
    int N;
    
    for(scanf("%d", &N); N>0; N--)
    {
        lld a, c;
        scanf("%lld%lld", &a, &c);
        printf("%lld\n", solve(a, c));
    }
}
