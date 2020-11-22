/*

suffix array (prefix doubling, counting sort, vector), LCP (Kasai's algorithm, vector)

O(nlogn)

*/

#include"stdafx.h"

#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
using namespace std;

typedef long long lld;

int main()
{
	string s;
	cin >> s;
	int n = s.length(), a = max(128, n);
	vector<int> sa(n), sa2(n), r(n), r2(n), c(a);
	for (int i = 0; i < n; i++)
		c[r[i] = s[i]]++;
	for (int i = 1; i < a; i++)
		c[i] += c[i - 1];
	for (int i = n - 1; i >= 0; i--)
		sa[--c[s[i]]] = i;
	for (int N = 1; N < n; N *= 2)
	{
		sa2.clear();
		for (int i = n - N; i < n; i++)
			sa2.push_back(i);
		for (int i = 0; i < n; i++)
			if (sa[i] - N >= 0)
				sa2.push_back(sa[i] - N);
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
			if (r[sa[i - 1]] == r[sa[i]] && sa[i - 1] + N < n && r[sa[i - 1] + N] == r[sa[i] + N])
				r2[sa[i]]--;
		}
		r.swap(r2);
		a = r[sa[n - 1]] + 1;
		c.resize(a);
		if (a == n)
			break;
	}
	vector<int> lcp(n), rsa(n);
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
