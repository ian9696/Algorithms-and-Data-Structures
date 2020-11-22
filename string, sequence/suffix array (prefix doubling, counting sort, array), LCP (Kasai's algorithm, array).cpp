/*

suffix array (prefix doubling, counting sort, array), LCP (Kasai's algorithm, array)

O(nlogn)

*/

#include"stdafx.h"

#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;

typedef long long lld;

const int N = 100000;
char s[N + 2];
int sa[N + 2], sa2[N + 2], r[N + 2], r2[N + 2], c[N + 2];
int n, a = 128;
int lcp[N + 2], rsa[N + 2];

int main()
{
	scanf("%s", s);
	n = strlen(s);
	for (int i = 0; i < n; i++)
		c[r[i] = s[i]]++;
	for (int i = 1; i < a; i++)
		c[i] += c[i - 1];
	for (int i = n - 1; i >= 0; i--)
		sa[--c[r[i]]] = i;
	for (int l = 1; l < n; l *= 2)
	{
		int p = 0;
		for (int i = n - l; i < n; i++)
			sa2[p++] = i;
		for (int i = 0; i < n; i++)
			if (sa[i] - l >= 0)
				sa2[p++] = sa[i] - l;
		for (int i = 0; i < a; i++)
			c[i] = 0;
		for (int i = 0; i < n; i++)
			c[r[i]]++;
		for (int i = 1; i < a; i++)
			c[i] += c[i - 1];
		for (int i = n - 1; i >= 0; i--)
			sa[--c[r[sa2[i]]]] = sa2[i];
		r2[sa[0]] = 0;
		for (int i = 1; i < n; i++)
		{
			r2[sa[i]] = r2[sa[i - 1]] + 1;
			if (r[sa[i - 1]] == r[sa[i]] && sa[i - 1] + l < n && r[sa[i - 1] + l] == r[sa[i] + l])
				r2[sa[i]]--;
		}
		for (int i = 0; i < n; i++)
			swap(r[i], r2[i]);
		a = r[sa[n - 1]] + 1;
		if (a == n)
			break;
	}
	for (int i = 0; i < n; i++)
		rsa[sa[i]] = i;
	for (int i = 0, k = 0; i < n; i++, k = max(0, k - 1))
	{
		if (rsa[i] == n - 1)
		{
			lcp[rsa[i]] = k = 0;
			continue;
		}
		int j = sa[rsa[i] + 1];
		while (max(i, j) + k < n && s[i + k] == s[j + k])
			k++;
		lcp[rsa[i]] = k;
	}
}
