/*

rolling hash

http://codeforces.com/problemset/problem/25/E

*/

#include "stdafx.h"

#include<stdio.h>
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;

typedef long long lld;

const lld P = 1000000007;
lld x = 37, x2;
string s[3], emp;
lld ans;

lld modpow(lld a, lld b)
{
	a %= P;
	return b == 0 ? 1 : modpow(a*a, b >> 1)*(b & 1 ? a : 1) % P;
}

lld inv(lld a)
{
	return modpow(a, P - 2);
}

bool contain(string &s, string &t)
{
	int ls = s.length(), lt = t.length();
	if (ls < lt)
		return false;
	lld vs = 0, vt = 0, y = modpow(x, lt - 1);
	for (lld i = 0, b = 1; i < lt; i++, b = b*x%P)
		vt = (vt + b*t[i]) % P;
	for (lld i = 0, b = 1; i < lt; i++, b = b*x%P)
		vs = (vs + b*s[i]) % P;
	for (lld i = lt - 1; i < ls; i++)
	{
		if (vs == vt)
			return true;
		if (i == ls - 1)
			return false;
		vs = (vs - s[i - lt + 1] + P) % P;
		vs = vs*x2%P;
		vs = (vs + y*s[i + 1]) % P;
	}
}

void sol3(string &s, string &t, string &u)
{
	for (int k = 0; k < 2; k++)
	{
		int ls = s.length(), lt = t.length(), lu = u.length();
		lld d = 0;
		for (lld i = 0, j = lt - 1, vu = 0, vt = 0, b = 1; i < lu - 1 && j>0; i++, j--, b = b*x%P)
		{
			vu = (vu + b*u[i]) % P;
			vt = (vt*x + t[j]) % P;
			if (vu == vt)
				d = i + 1;
		}
		ans = min(ans, ls + lt + lu - d);
		for (lld i = 0, j = ls - 1, vt = 0, vs = 0, b = 1; i < lt - 1 && j>0; i++, j--, b = b*x%P)
		{
			vt = (vt + b*t[i]) % P;
			vs = (vs*x + s[j]) % P;
			if (vt == vs)
				ans = min(ans, ls + lt - (i + 1) + lu - d);
		}
		s.swap(t);
	}
}

int main()
{
	x2 = inv(x);
	cin >> s[0] >> s[1] >> s[2];
	for (int i = 3; i > 1; i--)
		for (int j = 0; j < i - 1; j++)
			if (s[j].length() > s[j + 1].length())
				s[j].swap(s[j + 1]);
	ans = s[0].length() + s[1].length() + s[2].length();
	bool b21 = contain(s[2], s[1]);
	bool b20 = contain(s[2], s[0]);
	bool b10 = contain(s[1], s[0]);
	if (b21 && b20)
		ans = s[2].length();
	else if (b21)
		sol3(s[0], s[2], emp);
	else if (b20 || b10)
		sol3(s[1], s[2], emp);
	else
		for (int i = 0; i < 3; i++)
			sol3(s[(i + 1) % 3], s[(i + 2) % 3], s[i]);
	printf("%d\n", ans);
}
