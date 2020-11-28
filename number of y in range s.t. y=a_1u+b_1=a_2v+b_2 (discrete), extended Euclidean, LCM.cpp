/*

number of y in range s.t. y=a_1u+b_1=a_2v+b_2 (discrete), extended Euclidean, LCM

Educational Codeforces Round 16
D. Two Arithmetic Progressions
https://codeforces.com/contest/710/problem/D

*/

#include<stdio.h>
#include<algorithm>
using namespace std;

typedef long long lld;

lld ext_gcd(lld a, lld b, lld &x, lld &y)
{
	if (b == 0)
	{
		x = 1, y = 0;
		return a;
	}
	lld g = ext_gcd(b, a%b, y, x);
	y -= x*(a / b);
	return g;
}

lld gcd(lld a, lld b)
{
	lld x, y;
	return ext_gcd(a, b, x, y);
}

lld inv(lld a, lld b)
{
	lld x, y, g = ext_gcd(a, b, x, y);
	return (x%b + b) % b;
}

int main()
{
	lld a, b, a2, b2, L, R;
	scanf("%lld%lld%lld%lld%lld%lld", &a, &b, &a2, &b2, &L, &R);
	if (b < b2)
		swap(a, a2), swap(b, b2);
	lld ans = -1;
	if (gcd(a, a2) == 1)
	{
		lld x = ((inv(a, a2)*(b2 - b) % a2) + a2) % a2;
		lld lcm = a*a2;
		lld sam = b + a*x;
		lld u = sam > R ? 0 : (R - sam) / lcm + 1;
		lld d = sam > L - 1 ? 0 : (L - 1 - sam) / lcm + 1;
		ans = u - d;
	}
	else
	{
		lld g = gcd(a, a2);
		if ((b - b2) % g != 0)
			ans = 0;
		else
		{
			lld c = a / g, c2 = a2 / g;
			lld x = (inv(c, c2)*((b2 - b) / g) % c2 + c2) % c2;
			lld lcm = c*c2*g;
			lld sam = b + a*x;
			lld u = sam > R ? 0 : (R - sam) / lcm + 1;
			lld d = sam > L - 1 ? 0 : (L - 1 - sam) / lcm + 1;
			ans = u - d;
		}
	}
	printf("%lld\n", ans);
}
