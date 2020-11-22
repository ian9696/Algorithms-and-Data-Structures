/*

1d range update range query, 1d BIT

O(log(n))

Contest Approach to [types of] Binary Indexed Trees
https://web.archive.org/web/20150818144931/http://coutcode.com/blog/binaryindexedtree/

*/

#include "stdafx.h"

#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<algorithm>
#include<vector>
#include<stack>
#include<map>
#include<set>
#include<queue>
#include<string>
#include<string.h>
#include<math.h>
#include<ctype.h>
#include<bitset>
#include<deque>
using namespace std;

typedef long long ll;

struct PRBIT
{
	int n;
	vector<int> v;
	PRBIT(int _n) :n(_n), v(_n+1, 0)
	{
	}
	void pupdate(int x, int val)
	{
		while (x <= n)
		{
			v[x] += val;
			x += x&-x;
		}
	}
	int rquery(int x)
	{
		int res = 0;
		while (x > 0)
		{
			res += v[x];
			x -= x&-x;
		}
		return res;
	}
};

struct RRBIT
{
	PRBIT obit, cbit;
	int n;
	RRBIT(int _n) :n(_n), obit(_n), cbit(_n)
	{
	}
	void rupdate(int l, int r, int val)
	{
		obit.pupdate(l, val);
		obit.pupdate(r, -val);
		cbit.pupdate(l, val*(l - 1));
		cbit.pupdate(r, -val*(r-1));
		//show();
	}
	int rquery(int l, int r)
	{
		return ((r-1)*obit.rquery(r-1)-cbit.rquery(r-1)) - ((l-1)*obit.rquery(l-1)-cbit.rquery(l-1));
	}
	void show()
	{
		for (int i = 1; i <= n; i++)
		{
			printf("%d%s", rquery(i, i+1), i==n?"\n":" ");
		}
	}
};

int main()
{
	int n;
	scanf("%d", &n);
	RRBIT bit(n);
	for (int c, l, r, v; scanf("%d%d%d%d", &c, &l, &r, &v);)
	{
		if (c)
			bit.rupdate(l, r, v);
		else
			printf("ans : %d\n", bit.rquery(l , r));
	}

	system("pause");
	return 0;
}
