/*

Z algorithm

Given a string S of length n, the Z algorithm produces an array Z where Z[i] is the length of the longest substring starting from S[i] which is also a prefix of S.

O(n)

http://codeforces.com/contest/126/problem/B

*/

#include "stdafx.h"

#include<iostream>
#include<string.h>
using namespace std;

char s[1000001];
int z[1000000];

int main(void)
{

	memset(s, 0, sizeof(s));
	cin >> s;
	memset(z, 0, sizeof(z));

	int n = strlen(s);
	int L = 0, R = 0;
	for (int i = 1; i < n; i++) {
		if (i > R) {
			L = R = i;
			while (R < n && s[R - L] == s[R]) R++;
			z[i] = R - L; R--;
		}
		else {
			int k = i - L;
			if (z[k] < R - i + 1) z[i] = z[k];
			else {
				L = i;
				while (R < n && s[R - L] == s[R]) R++;
				z[i] = R - L; R--;
			}
		}
	}

	/*
	for (int i = 0; i < n; i++)
		cout << s[i];
	cout << endl;
	for (int i = 0; i < n; i++)
		cout << "i :" << z[i];
	cout << endl;
	*/

	int ans = 0;
	int maxz = 0;
	for (int i = 1; i < n; i++)
	{
		if (z[i] == n - i && maxz >= n - i)
		{
			ans = i;
			break;
		}
		else
		{
			maxz = maxz>z[i] ? maxz : z[i];
		}
	}

	if (ans > 0)
	{
		for (int i = ans; i < n; i++)
			cout << s[i] ;
		cout << endl;
	}
	else
		cout << "Just a legend" << endl;
		
	system("pause");
	return 0;
}
